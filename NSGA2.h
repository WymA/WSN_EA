#ifndef NSGA2_H
#define NSGA2_H
#include "EABase.h"

class NSGA2Indiv
{
public:
    Indiv indiv ;

    int rank ;
    double crowd_dist ;

    int counter ;

    NSGA2Indiv() ;
    ~NSGA2Indiv() ;
};

//Compare function used;
bool CompareByPareto( const NSGA2Indiv &a, const NSGA2Indiv &b ) ;
bool CompareByNum(const NSGA2Indiv &a, const NSGA2Indiv &b ) ;
bool CompareByEnergy( const NSGA2Indiv& a, const NSGA2Indiv& b ) ;

class NSGA2: public EABase
{

private:
    vector<NSGA2Indiv> population ;
    vector<NSGA2Indiv> offspring ;
    vector<vector<NSGA2Indiv> > pareto_front ;

public:
    NSGA2() ;
    NSGA2(const Para &para );
    virtual ~NSGA2();

    void Initialize();
    QString SingleRun() ;
    int Execute() ;


    Indiv& getIndiv(const int &idx) ;

private:

    NSGA2Indiv* Tournament( NSGA2Indiv* ind1, NSGA2Indiv* ind2 ) ;

    void InitPopulation() ;
    void FastNondominatedSort() ;
    void CrowdDistAssign(vector<NSGA2Indiv>& set ) ;

    void GenMutation() ;
    void GenSelection() ;
    void Evaluation() ;

    //********************************************************************
    // Several sorting function declaration;
    //********************************************************************
    void SortByObj( vector<NSGA2Indiv>& set, const int& idx ) ;
    void SortByPareto( vector<NSGA2Indiv>& set ) ;

    double GetBestObj( const int& obj ) ;

    void PrintData() ;
};

#endif
