#include "MOEAD.h"



SubProblem::SubProblem()
{
}

SubProblem::~SubProblem()
{
}

MOEAD::MOEAD()
{
    qsrand ((unsigned int)QThread::currentThread()) ;
}

MOEAD::MOEAD(const Para &para)
{
    qDebug()<<"MOEAD:"<< QThread::currentThread() ;
    InitPara(para) ;
    scalar_num = pop_size - 1 ;
    qsrand ((unsigned int)this) ;
}

MOEAD::~MOEAD()
{
    population.clear();
}

Indiv& MOEAD::getIndiv( const int& idx )
{
    return population[idx].indiv ;
}

double MOEAD::DistVector( vector<double>& vec1, vector<double>& vec2 )
{
    double sum = 0.0 ;
    for( int i = 0 ; i < kObjNum ; i++ )
        sum += pow( (vec1[i]-vec2[i]), 2.0 ) ;

    return sqrt(sum) ;
}

void MOEAD::InitPop()
{
    for ( vector<SubProblem>::iterator it = population.begin() ;
          it != population.end() ; it++ ){

        InitGeneratorInd( &(it->indiv) ) ;
        EvaluateInd( &(it->indiv) ) ;

        UpdateRef( it->indiv ) ;
    }
}


void MOEAD::InitWeight()
{
    InitGeneratorInd( &ref_point ) ;
    EvaluateInd( &ref_point) ;

    Indiv temp(ref_point) ;
    temp.destrory() ;


    for ( int i = 0 ; i < pop_size ; i++ ){

        SubProblem sub ;

        sub.lambda.push_back( 1.0*(i)/scalar_num ) ;
        sub.lambda.push_back( 1.0*(scalar_num-i)/scalar_num ) ;

        population.push_back( sub ) ;
    }
}

void MOEAD::MinSort(double* dist, int* idx, const int& pop_size, const int& neigh) 
{
    for( int i = 0 ; i < neigh ; i++ )
        for( int j = i+1 ; j < pop_size; j++ )
            if( dist[i] > dist[j] ) {

                double temp = dist[i];
                dist[i]     = dist[j];
                dist[j]     = temp;

                int tmp     = idx[i];
                idx[i]      = idx[j];
                idx[j]      = tmp ;
            }
}



void MOEAD::InitNeigh()
{
    double *dist = new double[pop_size] ;
    int    *idx  = new int[pop_size] ;

    neigh_size = pop_size / 10 ;

    for ( int i = 0 ; i < pop_size ; i++ ){

        for( int j = 0 ; j < pop_size ; j++ ){

            dist[j] = DistVector( population[i].lambda, population[j].lambda ) ;
            idx[j]  = j ;
        }

        MinSort( dist, idx, pop_size, neigh_size ) ;

        for ( int k = 0 ; k < neigh_size ; k++ )
            population[i].neigh.push_back( idx[k] ) ;

    }

    delete []dist ;
    delete []idx ;
    return ;
}

void MOEAD::UpdateRef( const Indiv& ind )
{
    for ( int i = 0 ; i < kObjNum ; i++ )
        if ( ind.y_var[i] < ref_point.y_var[i] )
            ref_point.y_var[i] = ind.y_var[i] ;
}


void MOEAD::UpdateProblem( Indiv& ind, const int& idx )
{
    for ( int i = 0 ; i < neigh_size ; i++ ){

        int k = population[idx].neigh[i] ;
        double s1, s2 ;

        s1 = Scalarizing( population[k].indiv.y_var, population[k].lambda ) ;
        s2 = Scalarizing( ind.y_var, population[k].lambda ) ;

        if ( s2 < s1 )
            population[k].indiv = ind ;
    }
}


void MOEAD::Evolution()
{


    for ( int i = 0 ; i < population.size() ; i++ ){

        Indiv child1, child2 ;
        int r1 = qrand()%neigh_size ;
        int r2 = qrand()%neigh_size ;

        int p1 = population[i].neigh[r1] ;
        int p2 = population[i].neigh[r2] ;


        GenCrossInd( &population[p1].indiv, &population[p2].indiv, &child1, &child2 ) ;
        GenMutationInd( &child1 ) ;

        EvaluateInd( &child1 ) ;

        UpdateRef( child1 ) ;
        UpdateProblem( child1, i ) ;
    }
}

double MOEAD::Scalarizing( vector<double>& y_var, vector<double>& lambda )
{
    double max = -1.0e+30 ;
    for ( int i = 0 ; i < kObjNum ; i++ ){

        double diff = fabs( y_var[i] - ref_point.y_var[i] ) ;
        double eval ;
        if ( lambda[i] == 0 )
            eval = 0.00001 * diff ;
        else
            eval = diff * lambda[i] ;

        if ( eval > max )
            max = eval ;
    }

    return max ;
}

void MOEAD::GetBestObj( const int& obj )
{
    best_ind.y_var[obj] = population[0].indiv.y_var[obj] ;
    worst_ind.y_var[obj] = population[0].indiv.y_var[obj] ;

    for ( int i = 0 ;  i < population.size() ; i++ ){

        if ( best_ind.y_var[obj] > population[i].indiv.y_var[obj] )
            best_ind.y_var[obj] = population[i].indiv.y_var[obj] ;

        if ( worst_ind.y_var[obj] < population[i].indiv.y_var[obj] )
            worst_ind.y_var[obj] = population[i].indiv.y_var[obj] ;
    }

}


void MOEAD::Initialize()
{

    population.clear();

    InitWeight() ;
    InitNeigh();
    InitPop() ;

    cur_gen = 1 ;
}

QString MOEAD::SingleRun()
{
    Evolution() ;

    double maxc = population[0].indiv.converage ;

    for ( int i = 0 ; i < population.size() ; i++ )
        if ( population[i].indiv.converage > maxc )
            maxc = population[i].indiv.converage ;

    GetBestObj( kObjNodes ) ;
    GetBestObj( kObjEnergy ) ;

    QString output ;

    output.append( "Gen "+ QString::number(cur_gen) +": " );
    output.append( " Nodes=" + QString::number( best_ind.y_var[kObjNodes] ) ) ;
    output.append( " Energy=" + QString::number( best_ind.y_var[kObjEnergy] ) ) ;
    output.append( " Converage: " + QString::number(maxc) ) ;

    qDebug() << output ;


    cur_gen++ ;

    return output ;
}

int MOEAD::Execute()
{

    for (  ; cur_gen <= total_gen   ; cur_gen++ ){

        //singleRun = true ;
        SingleRun() ;


   }
}
