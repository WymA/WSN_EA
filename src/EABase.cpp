#include "EABase.h"


TCompare Compare( const Indiv& ind1, const Indiv& ind2 )
{

    bool bBetter = false;
    bool bWorse = false;

    for ( int i = 0; !( bWorse && bBetter ) && ( i < kObjNum ) ; i++ ){

        if( ind1.y_var[i] < ind2.y_var[i] )
            bBetter = true;
        if( ind2.y_var[i] < ind1.y_var[i] )
            bWorse = true;
    }

    if (bWorse){

        if (bBetter)
            return kParetoNondominated;
        else
            return kParetoDominated;
    }else{

        if (bBetter)
            return kParetoDominating;
        else
            return kParetoEqual;
    }
}



inline int Distance( const XNode& point )
{
    return (int)sqrt( pow(double(point.x_pos-gxHECN), 2.0) +
                      pow(double(point.y_pos-gyHECN), 2.0) ) ;
}

inline int Distance( const XNode& point, const XNode& des)
{
    return (int)sqrt( pow(double(point.x_pos -des.x_pos), 2.0) +
                      pow(double(point.y_pos-des.y_pos), 2.0) ) ;
}


bool CompareByDist( const XNode& node1, const XNode& node2 )
{
    return Distance( node1 ) < Distance( node2 ) ;
}

Indiv::Indiv()
{
    cover_point = 0 ;
    coverage = 0.0 ;
    y_var = vector<double>(kObjNum, 0.0) ;
}

Indiv::~Indiv()
{
    x_var.clear();
    y_var.clear();
}

void Indiv::Insert( const vector<XNode>& vec )
{
    x_var.insert( x_var.end(), vec.begin(), vec.end() ) ;

    for ( int i = 0 ; i < x_var.size() ; i++ )
        SetCover( x_var[i] );
}

void Indiv::SetCover( const XNode& node )
{
    int x_sens, y_sens ;
    int X, Y, _X, _Y ;

    x_sens = node.x_pos ;
    y_sens = node.y_pos ;


    //Both index i and j are zero
    Y = y_sens ;
    X = x_sens ;
    field.field_map[Y][X]++ ;
    if ( 1 == field.field_map[Y][X] ) cover_point++ ;

    //Index i equals to zero
    Y = y_sens ;
    for ( int j = 1 ; j <= gRadSens ; j++ ){

        X = x_sens - j ;
        _X = x_sens + j ;

        if ( X < 0 ) X = gxHECN ;
        if ( _X >= gFieldLength ) _X = gxHECN ;

        field.field_map[Y][X]++ ;
        field.field_map[Y][_X]++ ;

        if ( 1 == field.field_map[Y][X] ) cover_point++ ;
        if ( 1 == field.field_map[Y][_X] ) cover_point++ ;

    }


    //Index j equals to zero
    X = x_sens ;
    for ( int i = 1 ; i <= gRadSens ; i++ ){

        Y = y_sens - i ;
        _Y = y_sens +i ;

        if ( Y < 0 ) Y = gyHECN ;
        if ( _Y >= gFieldLength ) _Y = gyHECN ;

        field.field_map[Y][X]++ ;
        field.field_map[_Y][X]++ ;

        if ( 1 == field.field_map[Y][X] ) cover_point++ ;
        if ( 1 == field.field_map[_Y][X] ) cover_point++ ;
    }

    //Neither index i or j is zero
    for ( int i = 1 ; i <= gRadSens ; i++ ){

        Y = y_sens - i ;
        _Y = y_sens + i ;
        if ( Y < 0 ) Y = gyHECN ;
        if ( _Y >= gFieldLength ) _Y = gyHECN ;

        for ( int j = 1 ; j <= gRadSens ; j++ ){

            X = x_sens - j ;
            _X = x_sens + j ;

            if ( X < 0 ) X = gxHECN ;
            if ( _X >= gFieldLength ) _X = gxHECN ;

            if ( i*i + j*j <= gRadSens*gRadSens  ) {

                field.field_map[Y][X]++ ;
                field.field_map[_Y][_X]++ ;
                field.field_map[_Y][X]++ ;
                field.field_map[Y][_X]++ ;

                if ( 1 == field.field_map[Y][X] ) cover_point++ ;
                if ( 1 == field.field_map[_Y][_X] ) cover_point++ ;
                if ( 1 == field.field_map[_Y][X] ) cover_point++ ;
                if ( 1 == field.field_map[Y][_X] ) cover_point++ ;

            }else
                break ;
        }
    }
}

void Indiv::RmPoint( const int& pnt )
{
    if ( !pnt ) return ;

    int x_sens, y_sens ;
    int X, Y, _X, _Y ;

    x_sens = x_var[pnt].x_pos ;
    y_sens = x_var[pnt].y_pos ;
    x_var.erase( x_var.begin() + pnt ) ;

    //Both index i and j are zero
    Y = y_sens ;
    X = x_sens ;
    field.field_map[Y][X]-- ;
    if ( 0 == field.field_map[Y][X] ) cover_point-- ;

    //Index i equals to zero
    Y = y_sens ;
    for ( int j = 1 ; j <= gRadSens ; j++ ){

        X = x_sens - j ;
        _X = x_sens + j ;

        if ( X < 0 ) X = gxHECN ;
        if ( _X >= gFieldLength ) _X = gxHECN ;

        field.field_map[Y][X]-- ;
        field.field_map[Y][_X]-- ;

        if ( 0 == field.field_map[Y][X] ) cover_point-- ;
        if ( 0 == field.field_map[Y][_X] ) cover_point-- ;

    }


    //Index j equals to zero
    X = x_sens ;
    for ( int i = 1 ; i <= gRadSens ; i++ ){

        Y = y_sens - i ;
        _Y = y_sens +i ;

        if ( Y < 0 ) Y = gyHECN ;
        if ( _Y >= gFieldLength ) _Y = gyHECN ;

        field.field_map[Y][X]-- ;
        field.field_map[_Y][X]-- ;

        if ( 0 == field.field_map[Y][X] ) cover_point-- ;
        if ( 0 == field.field_map[_Y][X] ) cover_point-- ;
    }

    //Neither index i or j is zero
    for ( int i = 1 ; i <= gRadSens ; i++ ){

        Y = y_sens - i ;
        _Y = y_sens + i ;
        if ( Y < 0 ) Y = gyHECN ;
        if ( _Y >= gFieldLength ) _Y = gyHECN ;

        for ( int j = 1 ; j <= gRadSens ; j++ ){

            X = x_sens - j ;
            _X = x_sens + j ;

            if ( X < 0 ) X = gxHECN ;
            if ( _X >= gFieldLength ) _X = gxHECN ;

            if ( i*i + j*j <= gRadSens*gRadSens  ) {

                field.field_map[Y][X]-- ;
                field.field_map[_Y][_X]-- ;
                field.field_map[_Y][X]-- ;
                field.field_map[Y][_X]-- ;

                if ( 0 == field.field_map[Y][X] ) cover_point-- ;
                if ( 0 == field.field_map[_Y][_X] ) cover_point-- ;
                if ( 0 == field.field_map[_Y][X] ) cover_point-- ;
                if ( 0 == field.field_map[Y][_X] ) cover_point-- ;

            }else
                break ;
        }
    }

}

void Indiv::AddPoint(const XNode& ref , int num )
{
    double a ;
    int _X, _Y ;
    int X, Y ;

    for ( int i = 0 ; i  < num ; i++ ){


        a = ( qrand()%360/1.0 ) * M_PI / 180 ;

        X = gFieldLength/2 + qrand()%( gFieldLength/2 ) ;
        Y = gFieldLength/2 + qrand()%( gFieldLength/2 ) ;
        int work = 0 ;
        for ( int d = gRadComm/2 + qrand()%( gRadComm/2 ) ;
              d < gFieldLength*kSqrt/2 ;
              d+=gRadComm/2 + qrand()%( gRadComm/2 ) ) {

            _X = ref.x_pos + d * cos(a) ;
            _Y = ref.y_pos + d * sin(a) ;

            if ( _Y < 0 ||
                 _Y >= gFieldLength ||
                 _X < 0 ||
                 _X >= gFieldLength )
                break ;

            if ( field.field_map[_Y][_X] == 1 ){

                work = 1 ;
                break ;
            }
            if ( field.field_map[_Y][_X] == 0 ){

                _X = X ;
                _Y = Y ;
                work = 1 ;
                break ;
            }
            X = _X ;
            Y = _Y ;
        }

        if ( work ) {

            XNode node ;
            node.x_pos = _X ;
            node.y_pos = _Y ;
            x_var.push_back( node );
            SetCover(x_var.back());
        }


    }
}


void Indiv::EvaluateCoverage( )
{
    //Percentages
    this->coverage = 100.0 * this->cover_point /
            (gFieldLength*gFieldLength) ;

    //    int counter = 0 ;
    //    for ( int i = 0 ; i < gFieldLength ; i++ )
    //        for ( int j = 0 ; j < gFieldLength ; j++ )
    //            if ( field.field_map[i][j] )
    //                counter++ ;

    //    cout<< counter<< ' '<< this->cover_point << endl ;

}

EABase::EABase():
    pop_size(0),
    cur_gen(0),
    total_gen(0),
    cross_rate(0.0),
    mutation_rate(0.0)
{
    qsrand( (unsigned int) this ) ;
}


EABase::~EABase()
{

}

void EABase::GenCrossInd( Indiv* ind1, Indiv* ind2, Indiv* child1, Indiv* child2  )
{
    double per = qrand()%1000 / 1000.0 ;

    if ( per < cross_rate &&
         ind1->x_var.size() > min_size &&
         ind2->x_var.size() > min_size ){

        /// \brief Crossover

        int area = qrand()%4 ;

        int X = gFieldLength/2 * ( area%2 ) ;
        int _X = X+gFieldLength/2 ;
        int Y = gFieldLength/2 * ( area/2 ) ;
        int _Y = Y + gFieldLength/2 ;

        vector<XNode> vec1, vec2 ;
        XNode hecn(gxHECN, gyHECN ) ;

        vec1.push_back( hecn );
        vec2.push_back( hecn );

        for ( int i = 1 ; i < ind1->x_var.size() ; i++ )
            if ( ind1->x_var[i].x_pos >= X && ind1->x_var[i].x_pos < _X &&
                 ind1->x_var[i].y_pos >= Y && ind1->x_var[i].y_pos < _Y ){

                vec2.push_back( ind1->x_var[i] ) ;
            }else
                vec1.push_back( ind1->x_var[i] );

        for ( int i = 1 ; i < ind2->x_var.size() ; i++ )
            if ( ind2->x_var[i].x_pos >= X && ind2->x_var[i].x_pos < _X &&
                 ind2->x_var[i].y_pos >= Y && ind2->x_var[i].y_pos < _Y ){

                vec1.push_back( ind2->x_var[i] ) ;
            }else
                vec2.push_back( ind2->x_var[i] );


        child1->Insert( vec1 );
        child2->Insert( vec2 );


    }else{

        child1->Insert( ind1->x_var );
        child2->Insert( ind2->x_var );

    }

    return ;
}

void EABase::GenMutationInd( Indiv* ind )
{

    double per = qrand()%1000 / 1000.0 ;
    int mut_point = qrand()%( ind->x_var.size() ) ;

    if ( per < mutation_rate ) {

        per = qrand()%1000 / 1000.0 ;
        if ( per < 0.6 ){

            int d = qrand()%gRadComm ;
            double a = (qrand()%3600/10.0) * M_PI / 180 ;

            int x2 = ind->x_var[mut_point].x_pos + d* cos(a) ;
            int y2 = ind->x_var[mut_point].y_pos + d* sin(a) ;

            if ( x2 >= gFieldLength ) x2 = gFieldLength - 1 ;
            if ( x2 < 0 ) x2 = 0 ;
            if ( y2 >= gFieldLength ) y2 = gFieldLength - 1 ;
            if ( y2 < 0 ) y2 = 0 ;

            ind->x_var[mut_point].x_pos = x2 ;
            ind->x_var[mut_point].y_pos = y2 ;

        }else{

            per = qrand()%1000/1000.0 ;
            if ( ind->coverage >= 100 )
                ind->RmPoint(mut_point);
            else{

                int num = 100-ind->coverage + 1 ;

                for ( int i = 0 ; i < num ; i++ )
                    ind->AddPoint( ind->x_var[0] ) ;
            }
        }
    }

    //BuildConnectivity( ind ) ;
}

void EABase::BuildConnectivity( Indiv* ind )
{
    if ( ind->island.empty() )
        return ;

    for ( int i = 0 ; i < ind->island.size() ; i++ ){

        ind->AddPoint( ind->x_var[ind->island[i]] );
    }
}


void EABase::InitGeneratorInd( Indiv* ind )
{
    ind->x_var.clear() ;

    //This value equals four times the theoretical lower bound for the number of nodes necessary
    int num = 4 * pow(double(gFieldLength-1), 2.0 )/
            (M_PI* pow( double(gRadSens), 2.0 )) ;

    XNode hecn( gxHECN, gyHECN ) ;

    ind->x_var.push_back( hecn );
    ind->SetCover( ind->x_var.back());

    ind->AddPoint(ind->x_var[0], num ) ;

    return ;
}




void EABase::EvaluateInd( Indiv* ind )
{
    //First, evaluate converage
    EvaluateEnergy(ind) ;
    EvaluateNodes(ind) ;
    ind->EvaluateCoverage() ;

    //Penalty calculation ;
    double u = ( 100 - ind->coverage) / 100.0 ;
    double penalty ;

    //    if ( u <= 0.0 )
    //        penalty = 0 ;
    //    if ( 0.0 < u && u <= 0.001 )
    //        penalty = 100*u ;
    //    if ( 0.001 < u && u <= 0.01 )
    //        penalty = 200*u ;
    //    if ( 0.01 < u && u <= 0.1 )
    //        penalty = 500*u ;
    //    if ( 0.1 < u && u <= 1 )
    //        penalty = 1000*u ;
    //    if ( 1 < u )
    penalty = 10000*u ;
    if ( u > 0.000001 )
        penalty += 100 ;

    ind->y_var[kObjNodes] += penalty ;
    ind->y_var[kObjEnergy] += penalty ;
    ind->penalty = penalty ;

    //qDebug()<< penalty ;

}

void EABase::EvaluateEnergy( Indiv* ind )
{
    sort( ind->x_var.begin()+1, ind->x_var.end(), CompareByDist ) ;
    SetNeighbor( ind ) ;

    for ( int i = 0 ;  i < ind->x_var.size() ; i++ )
        ind->x_var[i].load = 0 ;

    double max = 0.0 ;
    for (  int i = ind->x_var.size()-1 ;  i > 0 ; i-- ){

        ind->x_var[i].load++ ;
        int relay = 0 ;

        for ( vector<int>::iterator nei = ind->x_var[i].neigh.begin() ;
              nei != ind->x_var[i].neigh.end(); nei++ )
            if ( Distance(ind->x_var[*nei]) <= Distance(ind->x_var[i]) )
                relay++ ;

        for ( vector<int>::iterator nei = ind->x_var[i].neigh.begin() ;
              nei != ind->x_var[i].neigh.end(); nei++ )
            if ( Distance(ind->x_var[*nei]) <= Distance(ind->x_var[i]) )
                ind->x_var[*nei].load += ind->x_var[i].load / relay ;

        if ( ind->x_var[i].load > max )
            max = ind->x_var[i].load ;
    }

    ind->y_var[kObjEnergy] = max ;
}



void EABase::EvaluateNodes( Indiv* ind )
{
    ind->y_var[kObjNodes] = ind->x_var.size() ;
}


void EABase::SetNeighbor( Indiv* ind )
{
    for ( int i = 0 ; i < ind->x_var.size() ; i++ ){

        ind->x_var[i].is_connected = false ;
        ind->x_var[i].neigh.clear() ;
    }

    ind->x_var[0].is_connected = true ;

    for ( int i = 0 ; i < ind->x_var.size() ; i++ ){

        for ( int j = i + 1 ; j < ind->x_var.size() ; j++ ){

            if ( Distance( ind->x_var[i], ind->x_var[j] ) <= gRadComm ){

                ind->x_var[j].is_connected = ind->x_var[j].is_connected | ind->x_var[i].is_connected ;
                ind->x_var[i].is_connected = ind->x_var[j].is_connected | ind->x_var[i].is_connected ;

            }
        }
    }

    ind->island.clear();

    for ( int i = 0 ; i < ind->x_var.size() ; i++ )
        if ( !ind->x_var[i].is_connected )
            ind->island.push_back( i );

    for ( int i = ind->island.size()-1 ; i >= 0  ; i-- )
        ind->RmPoint( ind->island[i] ) ;


    for ( int i = 0 ; i < ind->x_var.size() ; i++ ){

        for ( int j = i + 1 ; j < ind->x_var.size() ; j++ ){

            if ( Distance( ind->x_var[i], ind->x_var[j] ) <= gRadComm ){

                ind->x_var[j].neigh.push_back( i ) ;
                ind->x_var[i].neigh.push_back( j ) ;

            }
        }
    }

    //SetRoute(ind) ;

    return ;
}

void EABase::SetRoute( Indiv* ind )
{
    for ( int i = 0 ; i < ind->x_var.size() ; i++ )
        ind->x_var[i].is_connected = false ;

    ind->x_var[0].is_connected = true ;
    SetConnectivity( ind->x_var, ind->x_var[0].neigh ) ;

    vector<int> index ;
    for ( int i = 0 ; i < ind->x_var.size() ; i++ )
        if ( !ind->x_var[i].is_connected )
            index.push_back(i);

    for ( int i = 0 ; i < index.size() ; i++ )
        ind->RmPoint( index[i] );
}

void EABase::SetConnectivity( vector<XNode>& vec, vector<int>& index )
{
    for ( int i = 0 ; i < index.size() ; i++ ){

        if ( vec[index[i]].is_connected )
            continue ;

        vec[index[i]].is_connected = true ;
        SetConnectivity( vec, vec[index[i]].neigh ) ;
    }

    return ;
}


void EABase::InitPara(const Para &para)
{
    cross_rate = para.cross_rate ;
    mutation_rate = para.mutation_rate ;
    pop_size = para.pop_size ;
    total_gen = para.total_gen ;

    double q = 2* acos( 1.0* gRadComm/ ( 2*gRadSens) ) ;
    double overlap = pow( double( gRadSens), 2.0 ) * ( q - sin(q) ) ;
    double c = M_PI * pow( double( gRadSens), 2.0 ) ;

    min_size = ( pow( double( gFieldLength - 1 ), 2.0) - overlap ) / (c - overlap ) ;
}
