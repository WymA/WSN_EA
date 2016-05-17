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
    int pop_size ;
    int total_gen ;
    double cross_rate ;
    double mutation_rate ;
    
    Para(
         int p_size,
         int t_gen,
         double c_rate,
         double m_rate
         ):
        pop_size(p_size),
        total_gen(t_gen),
        cross_rate(c_rate),
        mutation_rate(m_rate)
    {  }
    ~Para()
    {

    }
};

/************************************************************************************
XNode class is the structure of routing tree nodes as well as the x variables ;
***************************************************************************************/
class XNode
{
public:
    int x_pos ;
    int y_pos ;

    bool is_connected ;
    double load ;
    vector<int> neigh ;

    XNode(){}
    XNode( int x, int y ):
        x_pos(x),
        y_pos(y)
    {

    }
};


/**********************************************************
Indiv class is the basic class of other individual class.
 **********************************************************/
class Indiv
{
public:

    vector<XNode> x_var ;
    vector<double> y_var ;

    vector<int> island ;

    double penalty ;
    double coverage ;
    int cover_point ;

    Field field ;

    Indiv() ;
    virtual ~Indiv() ;

    void EvaluateCoverage() ;
    void SetCover(const XNode &node ) ;
    void Insert( const vector<XNode>& vec ) ;
    void AddPoint(const XNode& ref, int num=1 ) ;
    void RmPoint( const int& pnt ) ;
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

    virtual QString SingleRun() = 0 ;
    virtual void Initialize() = 0 ;
    virtual int  Execute() = 0 ;
    void InitPara( const Para& para ) ;

    int getCurGen() { return cur_gen ; }
    int getSize() { return pop_size ; }
    virtual Indiv& getIndiv( const int& idx ) = 0 ;

    inline Indiv& getBestInd() { return best_ind ; }
    inline Indiv& getWorstInd() { return worst_ind ; }

protected:

    Indiv best_ind ;
    Indiv worst_ind ;

    //************************************************
    // Basic parameters of EA
    //***********************************************
    int pop_size ;
    int cur_gen ;
    int total_gen ;
    double cross_rate ;
    double mutation_rate ;
    int min_size ;


    void InitGeneratorInd(Indiv *ind) ;
    void BuildConnectivity( Indiv* ind ) ;
    void GenCrossInd(Indiv* ind1, Indiv* ind2, Indiv* child1, Indiv* child2 ) ;
    void GenMutationInd( Indiv* ind ) ;

    void SetNeighbor( Indiv* ind ) ;
    void SetRoute( Indiv* ind ) ;
    void SetConnectivity( vector<XNode>& vec, vector<int>& index ) ;

    void EvaluateInd( Indiv* ind ) ;
    void EvaluateEnergy( Indiv* ind ) ; //The function to evaluate energy depletion of WSN
    void EvaluateNodes( Indiv* ind ) ;
    void EvaluateConverage( Indiv* ind ) ; //The function to evaluate converage of WSN

};

#endif
