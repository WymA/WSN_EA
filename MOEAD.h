#ifndef MOEAD_H
#define MOEAD_H

#include "EABase.h"


class SubProblem
{
public:

    SubProblem() ;
    ~SubProblem() ;

    Indiv indiv ;

    vector<double> lambda ;
    vector<int>    neigh ;

};



class MOEAD : public EABase
{
private:
    vector<SubProblem> population ;
    Indiv ref_point ;

    int neigh_size ;
    int scalar_num ;

public:

    MOEAD() ;
    MOEAD(const Para& para );
    ~MOEAD() ;


    void Initialize() ;
    int Execute() ;
    QString SingleRun() ;

    Indiv& getIndiv(const int &idx) ;

private:


    void InitWeight() ;
    void InitNeigh() ;
    void InitPop() ;

    void UpdateRef( const Indiv& ind ) ;
    void UpdateProblem( Indiv& ind, const int& idx ) ;

    void Evolution() ;

    double Scalarizing( vector<double>& y_var, vector<double>& lambda ) ;
    double DistVector( vector<double>& vec1, vector<double>& vec2 ) ;
    void MinSort(double* dist, int* idx, const int& pop_size, const int& neigh) ;

    double GetBestObj( const int& obj ) ;
};



#endif
