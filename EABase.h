#ifndef EABASE_H
#define EABASE_H

#include <iostream>
#include <QtCore/qmath.h>
#include <QtGlobal>
#include <QTime>
#include <QThread>
#include <QDebug>

#include "Constants.h"
#include "Field.h"


using namespace std;



/***********************************************************************
The constant value is defined as follow
 ***********************************************************************/
const double kInfinite = 1.0e+30 ;
const double kSqrt2 = 1.4142 ;

const int kObjNum = 2 ;
const int kObjNodes = 0 ;
const int kObjEnergy = 1 ;


enum TCompare
{
    kParetoDominating,
    kParetoDominated,
    kParetoNondominated,
    kParetoEqual
}; 

/**************************************************************
Para class is the structure of all the parameters
will be used in the EA process. All the members of
this class are public accessed.
 **************************************************************/
class Para
{
public:
    Field* field_map ;

    int pop_size ;
    int total_gen ;
    double cross_rate ;
    double mutation_rate ;
    
    Para(Field* field,
         int p_size,
         int t_gen,
         double c_rate,
         double m_rate
         ):  field_map(field) ,
        pop_size(p_size),
        total_gen(t_gen),
        cross_rate(c_rate),
        mutation_rate(m_rate)
    {  }
};

/************************************************************************************
XNode class is the structure of routing tree nodes as well as the x variables ;
***************************************************************************************/
class XNode
{
public:
    int x_pos ;
    int y_pos ;

    vector<XNode*> neigh ;
    XNode* parent ;

    double load ;

    XNode()
    {
        parent = NULL ;
    }

    XNode( const XNode& node ):
        x_pos(node.x_pos),
        y_pos(node.y_pos)
    {
        parent = NULL ;
    }

    ~XNode()
    {
        neigh.clear();
    }
};


/**********************************************************
Indiv class is the basic class of other individual class.
 **********************************************************/
class Indiv
{
private:


public:

    XNode* x_var ;
    vector<double> y_var ;

    double penalty ;
    double converage ;
    int size ;

    Indiv( const Indiv& ind ) ;
    Indiv() ;
    virtual ~Indiv() ;

    Indiv& operator=( const Indiv& other ) ;


    void destrory() ;
    XNode *randomize() ;
    XNode *randLeaf(int &idx) ;

    void insert(XNode *parent, const XNode &x ) ;
    void remove( XNode* node ) ;

    XNode* getNode( const int& idx, XNode *fetch = 0 ) ;
    void setCenter( const XNode& x ) ;

    int height( XNode* node ) ;

    void buildTree(vector<XNode> &vec, XNode* node ) ;
    void clone(XNode *des, XNode *src ) ;

    XNode randGenerator( XNode* node ) ;

    void adjusRandNode() ;
    void addRandNode( ) ;
    void rmRandNode() ;

    void clearLoad(XNode *node) ;

    void getVector(vector<XNode> &output, XNode* node ) ;


    //********************************************************************
    // Evaluation functions
    //********************************************************************
    void EvaluateEnergy( ) ; //The function to evaluate energy depletion of WSN
    void EvaluateNodes( ) ;
    void EvaluateConverage(Field *field) ; //The function to evaluate converage of WSN
    void Converage(XNode *node, Field* field ) ;
    double Energy( XNode* node, const int& distance) ;
};


/*****************************************************************************
Compare function: This function is to compare this object to another ind2 and
then return a integer value.
******************************************************************************/
TCompare Compare( const Indiv& ind1, const Indiv& ind2 ) ;

inline int  Distance( const XNode& point ) ;
inline int  Distance( const XNode& point, const XNode& des ) ;


/**************************************************
EABase class is the basic class of other EA class.
 *************************************************/
class EABase
{
public:
    EABase() ;
    virtual ~EABase() ;

    virtual void SingleRun() = 0 ;
    virtual void Initialize() = 0 ;
    virtual int  Execute() = 0 ;
    void InitPara( const Para& para ) ;

    int getCurGen() { return cur_gen ; }
    int getSize() { return pop_size ; }
    virtual Indiv& getIndiv( const int& idx ) = 0 ;


protected:

    Field* field ;
    //************************************************
    // Basic parameters of EA
    //***********************************************
    int pop_size ;
    int cur_gen ;
    int total_gen ;
    double cross_rate ;
    double mutation_rate ;
    int min_size ;

    void InitGeneratorInd( Indiv* ind ) ;
    XNode PosGenerator() ;


    void GenCrossInd(Indiv* ind1, Indiv* ind2, Indiv* child1, Indiv* child2 ) ;
    void GenMutationInd( Indiv* ind ) ;

    void SetNeighbor( Indiv* ind ) ;
    void SetConnectivity(vector<XNode> &vec , vector<int> nei) ;


    void EvaluateInd( Indiv* ind ) ;

};

#endif
