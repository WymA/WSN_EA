/*************************************************************************
This .cpp file contains the implementation of NSGA2's details.
*************************************************************************/
#include "NSGA2.h"


NSGA2Indiv::NSGA2Indiv():
    rank(0), crowd_dist(0.0), counter(0)
{
}

NSGA2Indiv::~NSGA2Indiv()
{
}


//Tool function .
bool CompareByNum( const NSGA2Indiv& a, const NSGA2Indiv& b )
{
    return ( a.indiv.y_var[kObjNodes] < b.indiv.y_var[kObjNodes] ) ;
}

bool CompareByEnergy(const NSGA2Indiv &a, const NSGA2Indiv &b )
{
    return ( a.indiv.y_var[kObjEnergy] < b.indiv.y_var[kObjEnergy ] ) ;
}

bool CompareByPareto(const NSGA2Indiv &a, const NSGA2Indiv &b )
{
    TCompare res = Compare( a.indiv, b.indiv ) ;

    if ( res == kParetoDominating ||
         res == kParetoEqual &&
         a.crowd_dist > b.crowd_dist )
        return true ;
    else
        return false ;

}



//**************************************************************************
// Implementation of members in class NSGA2
//**************************************************************************

NSGA2::NSGA2()
{
    qsrand ((unsigned int)QThread::currentThread()) ;
}

NSGA2::NSGA2(const Para &para )
{

    InitPara(para) ;
    qsrand ((unsigned int)QThread::currentThread()) ;
}

NSGA2::~NSGA2()
{
    population.clear() ;
    offspring.clear() ;
    pareto_front.clear() ;
}

Indiv &NSGA2::getIndiv(const int& idx )
{
    return population[idx].indiv ;
}

void NSGA2::InitPopulation()
{
    population.clear() ;
    offspring.clear() ;
    pareto_front.clear() ;

    for ( int i = 0 ; i < pop_size ; i++){

        NSGA2Indiv ind  ;
        InitGeneratorInd( &ind.indiv ) ;
        population.push_back( ind ) ;
    }

}

void NSGA2::FastNondominatedSort()
{
    for ( int i = 0 ; i < pareto_front.size() ; i++ )
        pareto_front[i].clear() ;
    pareto_front.clear();

    vector<NSGA2Indiv> next_front ;


    for ( int i = 1 ; !population.empty() ; i++ ){

        next_front.clear() ;
        for ( int p = 0 ; p < population.size() ; p++ ){

            population[p].counter = 0 ;

            for ( int q = 0 ; q < population.size()  ; q++ ) {

                TCompare res = Compare( population[p].indiv, population[q].indiv ) ;
                if ( kParetoDominated == res )
                    population[p].counter++ ;
            }

            if ( population[p].counter == 0 ){

                population[p].rank = i ;
                next_front.push_back( population[p] ) ;
                population.erase( population.begin() + p ) ;
            }

        }
        pareto_front.push_back( next_front ) ;

    }


    //  //Rank the rest of population
    //  for ( int i = 1 ; !pareto_front[i-1].empty() ; i++ ){

    //    next_front.clear() ;
    //    for ( int p = 0 ; p < pareto_front[i-1].size() ; p++ ) {

    //      for ( vector<NSGA2Indiv>::iterator itq = dominated_set[p].begin() ;
    //            itq != dominated_set[p].end() ; itq++ ){

    //        itq->counter-- ;
    //        if ( !itq->counter ){

    //          itq->rank =  i+1 ;
    //          next_front.push_back( *itq ) ;
    //        }

    //      }
    //    }
    //    pareto_front.push_back(next_front) ;
    //  }

    return ;
}


void NSGA2::CrowdDistAssign( vector<NSGA2Indiv>& set )
{

    int size = set.size() ;
    if ( !size ) return ;

    for ( vector<NSGA2Indiv>::iterator it = set.begin() ; it != set.end() ; it++ )
        it->crowd_dist = 0.0 ;

    for ( int i = 0 ; i < kObjNum ; i++ ){

        SortByObj(set, i ) ;
        set[0].crowd_dist = set[size-1].crowd_dist = kInfinite ;

        for ( int j = 1 ; j < size-1 ; j++ )
            set[j].crowd_dist += ( set[j+1].indiv.y_var[i] - set[j-1].indiv.y_var[i] ) ;

    }

    return ;
}

void NSGA2::GenSelection()
{
    int *a1, *a2;
    a1 = new int[pop_size];
    a2 = new int[pop_size];

    for( int i = 0; i < pop_size ; i++)
        a1[i] = a2[i] = i;

    int ran, temp ;
    for( int i = 0; i < pop_size - 1 ; i++ ){

        ran = i + qrand()%( pop_size - 1 - i ) ;
        temp = a1[ran];
        a1[ran] = a1[i];
        a1[i] = temp;

        ran = i + qrand()%( pop_size - 1 - i ) ;
        temp = a2[ran];
        a2[ran] = a2[i];
        a2[i] = temp;

    }

    offspring.clear() ;

    NSGA2Indiv *parent1, *parent2 ;
    for( int i = 0; i < pop_size ; i += 4 ){

        NSGA2Indiv child1, child2 ;

        parent1 = Tournament( &population[a1[i]], &population[a1[i+1]] );
        parent2 = Tournament( &population[a1[i+2]], &population[a1[i+3]] );
        GenCrossInd( &parent1->indiv, &parent2->indiv, &child1.indiv, &child2.indiv );
        offspring.push_back(child1) ;
        offspring.push_back(child2) ;

        NSGA2Indiv child3, child4 ;

        parent1 = Tournament( &population[a2[i]], &population[a2[i+1]] );
        parent2 = Tournament( &population[a2[i+2]], &population[a2[i+3]] );
        GenCrossInd( &parent1->indiv, &parent2->indiv, &child3.indiv, &child4.indiv );
        offspring.push_back(child3) ;
        offspring.push_back(child4) ;

    }

    delete []a1 ;
    delete []a2 ;
}

NSGA2Indiv* NSGA2::Tournament( NSGA2Indiv* ind1, NSGA2Indiv* ind2 )
{

    TCompare res = Compare( ind1->indiv, ind2->indiv ) ;

    if ( res == kParetoDominating ) return ind1 ;
    if ( res == kParetoDominated ) return ind2 ;

    if ( ind1->crowd_dist >= ind2->crowd_dist ) return ind1 ;
    else return ind2 ;

}


/***************************************************************
The implementation of several sorting functions
*****************************************************************/
void NSGA2::SortByObj( vector<NSGA2Indiv>& set, const int& idx )
{
    if ( idx == kObjNodes )
        sort(set.begin(), set.end(), CompareByNum ) ;
    if ( idx == kObjEnergy )
        sort(set.begin(), set.end(), CompareByEnergy ) ;

    return ;
}


void NSGA2::SortByPareto( vector<NSGA2Indiv>& set )
{
    sort( set.begin(), set.end(), CompareByPareto ) ;
}


void NSGA2::Evaluation()
{

    for ( vector<NSGA2Indiv>::iterator it = population.begin() ;
          it != population.end() ; it++ ){

        EvaluateInd( &(it->indiv) ) ;
    }
}



void NSGA2::GenMutation()
{

    for ( vector<NSGA2Indiv>::iterator it = population.begin() ;
          it != population.end() ; it++ )
        GenMutationInd( &(it->indiv) ) ;

}

double NSGA2::GetBestObj( const int& obj )
{
    SortByObj( population, obj ) ;

    return population[0].indiv.y_var[obj] ;
}

void NSGA2::PrintData()
{
    double maxc = population[0].indiv.converage ;

    for ( int i = 0 ; i < population.size() ; i++ )
        if ( population[i].indiv.converage > maxc )
            maxc = population[i].indiv.converage ;

    cout<< "Energy: "<<GetBestObj(kObjEnergy) << ' ' ;
    cout<< "Nodes: " <<GetBestObj(kObjNodes) << ' ' ;
    cout<< "Converage: " << maxc << endl ;
}

void NSGA2::Initialize()
{
    InitPopulation() ;
    Evaluation() ;
    cur_gen = 1 ;
}

QString NSGA2::SingleRun()
{
    cout<< "Gen " << cur_gen << ":  " ;

    //Reproduce the offspring
    //clock_t start, end ;
    //clock_t t_start, t_end ;
    //t_start = clock() ;

    GenSelection()  ;
    GenMutation() ;

    population.insert( population.end(), offspring.begin(), offspring.end() ) ;

    //start = clock() ;
    Evaluation() ;
    //end = clock() ;
   // cout<< "Eval : "<< double(end-start)/CLOCKS_PER_SEC <<' ' ;

    //start = clock() ;
    FastNondominatedSort() ;
    //end = clock() ;
    //cout<< "FNS : "<< double(end-start)/CLOCKS_PER_SEC <<endl ;

    //Select for the next generation ;
    population.clear() ;

    int i ;
    for ( i = 0 ;
          (i < pareto_front.size()) && (population.size()+pareto_front[i].size() < pop_size);
          i++ ) {

        CrowdDistAssign( pareto_front[i] ) ;
        population.insert( population.end(), pareto_front[i].begin(), pareto_front[i].end() );


    }

    if ( population.size() < pop_size ){

        SortByPareto( pareto_front[i] ) ;
        population.insert( population.end(), pareto_front[i].begin(),
                           pareto_front[i].begin() + pop_size - population.size() );//Offset
    }

    cur_gen++ ;

    PrintData() ;
    //t_end = clock();
    //cout<< "Total time: "<< double(t_end-t_start)/CLOCKS_PER_SEC <<endl ;

}


int NSGA2::Execute()
{

    for (   ;  cur_gen <= total_gen ; cur_gen++ ){

        //singleRun = true ;
        SingleRun() ;
        //singleRun = false ;
    }

    return 0 ;
}

