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


Indiv::Indiv( const Indiv& ind )
{
    if ( this != &ind ){

        x_var = new XNode ;
        x_var->x_pos = gxHECN ;
        x_var->y_pos = gyHECN ;
        x_var->parent = NULL ;
        x_var->neigh.clear();
        size = 1 ;

        clone( this->x_var, ind.x_var );
        this->y_var = ind.y_var ;
        this->converage = ind.converage ;
    }
}

Indiv& Indiv::operator=( const Indiv& ind )
{

    if ( this != &ind ){

        if ( this->x_var )
            destrory();

        x_var = new XNode ;
        x_var->x_pos = gxHECN ;
        x_var->y_pos = gyHECN ;
        x_var->parent = NULL ;
        x_var->neigh.clear();
        size = 1 ;

        clone( this->x_var, ind.x_var );
        this->y_var = ind.y_var ;
        this->converage = ind.converage ;

        return *this ;
    }
}


Indiv::Indiv()
{
    x_var = new XNode ;
    x_var->x_pos = gxHECN ;
    x_var->y_pos = gyHECN ;
    x_var->parent = NULL ;
    x_var->neigh.clear();
    size = 1 ;

    y_var = vector<double>(kObjNum, 0.0) ;
}

Indiv::~Indiv()
{
    destrory() ;
    y_var.clear();
}

void Indiv::setCenter( const XNode& x )
{
    if ( x_var )
        delete x_var ;

    x_var = new XNode(x) ;
    x_var->parent = NULL ;
    size = 1 ;
}

void Indiv::insert( XNode* parent , const XNode& x )
{
    XNode* new_node = new XNode(x) ;
    new_node->parent = parent ;
    parent->neigh.push_back(new_node);

    size++ ;

    return ;
}

void Indiv::clone( XNode* des, XNode* src )
{
    for ( int i = 0 ; i < src->neigh.size() ; i++ )
        this->insert( des, *src->neigh[i] ) ;

    for ( int i = 0 ; i < src->neigh.size() ; i++ )
        clone( des->neigh[i], src->neigh[i] ) ;
}

int Indiv::height( XNode* node )
{
    if ( node->neigh.empty() )
        return 0 ;

    int h = 0 ;

    for ( int i = 0 ; i < node->neigh.size() ; i++ ){

        int tmp = height( node->neigh[i] ) ;
        if ( tmp > h )
            h = tmp ;
    }

    return h +1 ;
}

XNode* Indiv::randomize( )
{
    int n = qrand() % ( height( this->x_var )+1 );

    XNode* tmp = x_var ;

    for ( int i = 0 ; i < n ; i++ ){

        if ( tmp->neigh.empty() )
            break ;

        int idx = qrand() % tmp->neigh.size() ;
        tmp = tmp->neigh[idx] ;
    }
    return tmp ;
}


void Indiv::destrory()
{
    remove(x_var) ;
}

void Indiv::remove( XNode* node )
{
    if ( node ) {

        for ( int i = 0 ; i < node->neigh.size() ; i++ )
            remove( node->neigh[i] ) ;

        delete node ;
        node = NULL ;
        size-- ;

    }
}

XNode* Indiv::randLeaf(int &idx )
{
    idx = -1 ;
    XNode* parent = x_var  ;

    if ( parent->neigh.empty() )
        return parent ;

    for ( ; ; ){

        idx = qrand() % parent->neigh.size() ;

        if ( parent->neigh[idx]->neigh.empty() )
            break ;
        else
            parent = parent->neigh[idx] ;
    }

    return parent ;
}


void Indiv::rmRandNode()
{
    int idx ;
    XNode* parent = randLeaf( idx ) ;

    if ( idx != -1 ) {

        delete parent->neigh[idx] ;
        parent->neigh.erase( parent->neigh.begin() + idx ) ;
        size-- ;
    }
}

void Indiv::getVector( vector<XNode>& output, XNode* node )
{
    output.push_back( *node );

    for ( int i = 0 ; i < node->neigh.size() ; i++ )
        getVector( output, node->neigh[i] );
}

XNode Indiv::randGenerator( XNode* node )
{
    int d = qrand()%gRadComm ;
    double a = (qrand()%3600/10.0) * M_PI / 180 ;

    int x2  = node->x_pos + d* cos(a) ;
    int y2  = node->y_pos + d* sin(a) ;

    if ( x2 >= gFieldLength ) x2 = gFieldLength - 1 ;
    if ( x2 < 0 ) x2 = 0 ;
    if ( y2 >= gFieldLength ) y2 = gFieldLength - 1 ;
    if ( y2 < 0 ) y2 = 0 ;

    XNode new_node ;
    new_node.x_pos = x2 ;
    new_node.y_pos = y2 ;

    return new_node ;
}

void Indiv::adjusRandNode()
{
    XNode* parent ;
    int idx ;
    parent = randLeaf( idx )  ;

    if ( idx != -1 ) {

        parent->neigh.erase( parent->neigh.begin() + idx ) ;
        size-- ;
        insert( parent, randGenerator( parent ) );
    }
}

void Indiv::addRandNode( )
{
    XNode* tmp ;
    tmp = randomize(  ) ;

    insert( tmp, randGenerator( tmp) );
}


void Indiv::clearLoad( XNode* node )
{
    node->load = 0 ;

    for ( int i = 0 ; i < node->neigh.size() ; i++ )
        clearLoad( node->neigh[i] );
}

void Indiv::buildTree( vector<XNode>& vec, XNode* node )
{
    for ( int i =0 ; i < vec.size() ; i++ )
        if ( Distance( *node, vec[i] ) <= gRadComm ){

            insert( node, vec[i]);
            vec.erase( vec.begin() + i ) ;
        }

    if ( vec.empty() )
        return ;

    for ( int i = 0 ; i < node->neigh.size() ; i++ )
        buildTree(  vec, node->neigh[i] ) ;
}


XNode* Indiv::getNode(const int& idx , XNode* fetch )
{
    //    if ( fetch == 0 )
    //        getNode( idx, x_var ) ;

    //    if ( idx == 0 )
    //        return fetch ;

    //    for ( int i = 0 ;  i < fetch->neigh.size() ; i++ )
    //        getNode( idx-1, fetch->neigh ) ;
}

void Indiv::EvaluateNodes( )
{
    y_var[kObjNodes] = size ;
}

double Indiv::Energy( XNode* node, const int& distance)
{
    double max = 0.0 ;
    double tmp ;
    for ( int i = 0 ; i < node->neigh.size() ; i++ ){

        tmp = Energy( node->neigh[i], distance );
        if ( max < tmp )
            max = tmp ;
    }

    if ( distance == Distance( *node ) ){

        node->load++ ;
        int relay = 0 ;

        for ( int i = 0 ; i < node->neigh.size() ; i++ )
            if ( Distance( *node->neigh[i] ) < Distance( *node ) )
                relay++ ;

        if ( Distance( *node->parent ) < Distance( *node ) )
            relay++ ;



        for ( int i = 0 ; i < node->neigh.size() ; i++ )
            if ( Distance( *node->neigh[i] ) < Distance( *node ) ){

                node->neigh[i]->load += node->load / relay ;
                if ( max < node->neigh[i]->load )
                    max = node->neigh[i]->load ;
            }

        if ( Distance( *node->parent ) < Distance( *node ) ){

            node->parent->load += node->load / relay ;
            if ( max < node->parent->load )
                max = node->parent->load ;
        }

        if ( max < node->load )
            max = node->load  ;
    }

    return max ;
}

void Indiv::EvaluateEnergy()
{
    clearLoad( x_var ) ;

    XNode n ;
    n.x_pos = 0 ;
    n.y_pos = 0 ;
    int distance = Distance(n) ;//the furthest distance from HECN

    double max = 0.0 ;
    double tmp ;
    while( distance > 0 ){

        tmp = Energy( x_var, distance ) ;
        if ( max < tmp )
            max = tmp ;
        distance-- ;
    }

    y_var[kObjEnergy] = max ;
}

void Indiv::Converage( XNode* node, Field* field )
{
    int x_sens, y_sens ;
    int X, Y ;
    int _X, _Y ;

    x_sens = node->x_pos ;
    y_sens = node->y_pos ;

    for ( int i = 0 ; i <= gRadSens ; i++ ){

        Y = y_sens - i ;
        _Y = y_sens + i ;
        if ( Y < 0 ) Y = 0 ;
        if ( _Y >= gFieldLength ) _Y = gFieldLength - 1 ;

        for ( int j = 0 ; j <= gRadSens ; j++ ){

            X = x_sens - j ;
            _X = x_sens + j ;

            if ( X < 0 ) X = 0 ;
            if ( _X >= gFieldLength ) _X = gFieldLength - 1 ;

            if ( i*i + j*j <= gRadSens*gRadSens  ) {

                field->field_map[Y][X] = 1 ;
                field->field_map[_Y][_X] = 1 ;
                field->field_map[_Y][X] = 1 ;
                field->field_map[Y][_X] = 1 ;
            }else
                break ;
        }
    }

    for ( int i = 0 ; i < node->neigh.size() ; i++ )
        Converage( node->neigh[i], field );

}

void Indiv::EvaluateConverage( Field* field )
{
    field->ClearMap() ;

    Converage( x_var, field ) ;

    //Percentages
    converage = 100.0 * field->ConveredPoint()/(gFieldLength*gFieldLength) ;
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
         ind1->size > min_size &&
         ind2->size > min_size
         ){



        //        int pnt1 = qrand() % ind1->x_var->neigh.size() ;
        //        int pnt2 = qrand() % ind2->x_var->neigh.size() ;
//        for ( int i = 0 ; i < ind2->x_var->neigh.size()  ; i++ )
//            if ( Distance( *ind2->x_var->neigh[i], *ind1->x_var->neigh[pnt1] )
//                 < gRadComm )
//                pnt2 = i ;

//        vector<XNode> vec1, vec2 ;

//        //This is the crossover part ;
//        ind1->getVector( vec1, ind2->x_var->neigh[pnt2] );
//        ind2->getVector( vec2, ind1->x_var->neigh[pnt1] );

//        //The other x variables copying
//        for ( int i = 0 ; i < ind1->x_var->neigh.size()  ; i++ )
//            if ( i != pnt1 )
//                ind1->getVector( vec1, ind1->x_var->neigh[i] );
//        for ( int i = 0 ; i < ind2->x_var->neigh.size()  ; i++ )
//            if ( i != pnt2 )
//                ind2->getVector( vec2, ind2->x_var->neigh[i] );

        int pnt1[2] ;
        int pnt2[2] ;

        pnt1[0] = qrand() % ind1->x_var->neigh.size() ;
        pnt1[1] = qrand() % ind1->x_var->neigh.size() ;

        pnt2[0] = qrand() % ind2->x_var->neigh.size() ;
        pnt2[1] = qrand() % ind2->x_var->neigh.size() ;

        for ( int i = 0 ; i < ind2->x_var->neigh.size()  ; i++ )
            if ( Distance( *ind2->x_var->neigh[i], *ind1->x_var->neigh[pnt1[0]] )
                 < gRadComm )
                pnt2[0] = i ;

        for ( int i = 0 ; i < ind2->x_var->neigh.size()  ; i++ )
            if ( Distance( *ind2->x_var->neigh[i], *ind1->x_var->neigh[pnt1[1]] )
                 < gRadComm && pnt2[0] != i)
                pnt2[1] = i ;

        vector<XNode> vec1, vec2 ;

        //This is the crossover part ;
        ind1->getVector( vec1, ind2->x_var->neigh[pnt2[0]] );
        ind1->getVector( vec1, ind2->x_var->neigh[pnt2[1]] );
        ind2->getVector( vec2, ind1->x_var->neigh[pnt1[0]] );
        ind2->getVector( vec2, ind1->x_var->neigh[pnt1[1]] );

        //The other x variables copying
        for ( int i = 0 ; i < ind1->x_var->neigh.size()  ; i++ )
            if ( i != pnt1[0] && i != pnt1[1] )
                ind1->getVector( vec1, ind1->x_var->neigh[i] );
        for ( int i = 0 ; i < ind2->x_var->neigh.size()  ; i++ )
            if ( i != pnt2[0] && i != pnt2[1])
                ind2->getVector( vec2, ind2->x_var->neigh[i] );

        //Build the child trees
        child1->buildTree( vec1, child1->x_var );
        child2->buildTree( vec2, child2->x_var );

    }else{

        //None crossing
        child1->clone( child1->x_var, ind1->x_var ) ;
        child2->clone( child2->x_var, ind2->x_var ) ;

    }
    return ;
}

void EABase::GenMutationInd( Indiv* ind )
{

    double per = qrand()%100 / 100.0 ;
    //int mut_point = 1 + qrand() % ( ind->x_var.size() - 1) ;

    if ( per < mutation_rate ) {

        per = qrand()%100 / 100.0 ;
        if ( per < 0.6 ){

            ind->adjusRandNode() ;

        }else{

            per = qrand()%100/100.0 ;

            if ( per < 0.5 )
                ind->rmRandNode() ; //ind->x_var.erase( ind->x_var.begin() + mut_point ) ;
            else
                ind->addRandNode();
        }
    }
}


void EABase::InitGeneratorInd( Indiv* ind )
{
    //ind->x_var.clear() ;
    XNode node ;
    node.x_pos = gxHECN ;
    node.y_pos = gyHECN ;

    ind->setCenter( node ); ;//The 1st value is the position of HECN

    //This value equals four times the theoretical lower bound for the number of nodes necessary
    int num = 4 * pow(double(gFieldLength-1), 2.0 )
            /(M_PI* pow( double(gRadSens), 2.0 )) ;

    vector<XNode> vec ;
    for ( int i = 1 ; i < num ; i++ )
        vec.push_back( PosGenerator()) ;

    ind->buildTree( vec, ind->x_var );

    return ;
}

XNode EABase::PosGenerator(  )
{
    double a = ( qrand()%3600/10.0 ) * M_PI / 180 ;

    int _X, _Y ;
    int d ;

    d = qrand() % (gFieldLength/2) ;

    _X = gxHECN + d * cos(a) ;
    _Y = gyHECN + d * sin(a) ;

    XNode node ;
    node.x_pos = _X ;
    node.y_pos = _Y ;

    return  node ;
}



void EABase::EvaluateInd( Indiv* ind )
{
    //First, evaluate converage
    ind->EvaluateConverage(field) ;
    ind->EvaluateEnergy() ;
    ind->EvaluateNodes() ;

    //Penalty calculation ;
    double u = ( 100 - ind->converage) / 100.0 ;
    double penalty ;

    if ( u <= 0.0 )
        penalty = 0 ;
    if ( 0.0 < u && u <= 0.001 )
        penalty = 100*u ;
    if ( 0.001 < u && u <= 0.01 )
        penalty = 200*u ;
    if ( 0.01 < u && u <= 0.1 )
        penalty = 500*u ;
    if ( 0.1 < u && u <= 1 )
        penalty = 1000*u ;
    if ( 1 < u )
        penalty = 10000*u ;

    ind->y_var[kObjNodes] += penalty ;
    ind->y_var[kObjEnergy] += penalty ;
    ind->penalty = penalty ;

    //qDebug()<< penalty ;

}


void EABase::SetNeighbor( Indiv* ind )
{
    //    for ( int i = 0 ; i < ind->x_var.size() ; i++ ){

    //        ind->x_var[i].neigh.clear() ;
    //        ind->x_var[i].is_connected = false ;
    //    }

    //    for ( int i = 0 ; i < ind->x_var.size() ; i++ ){

    //        for ( int j = i + 1 ; j < ind->x_var.size() ; j++ ){

    //            if ( Distance( ind->x_var[i], ind->x_var[j] ) <= gRadComm ){

    //                ind->x_var[i].neigh.push_back( &ind->x_var[j] ) ;
    //                ind->x_var[j].neigh.push_back( &ind->x_var[i] ) ;
    //            }

    //        }
    //    }//End of loop;

    //    ind->x_var[0].is_connected = true ;
    //    SetConnectivity( ind->x_var, ind->x_var[0].neigh ) ;



    //    for ( int i = 0 ; i < ind->x_var.size() ; i++ )
    //        if ( !ind->x_var[i].is_connected )
    //            ind->x_var.erase( ind->x_var.begin() + i ) ;

    return ;
}

void EABase::SetConnectivity( vector<XNode>& vec, vector<int> nei )
{

    //    for ( int i = 0 ; i < nei.size() ; i++ ){

    //        if ( vec[nei[i]].is_connected)
    //            continue ;


    //        SetConnectivity( vec, vec[nei[i]].neigh ) ;
    //        vec[nei[i]].is_connected = true ;
    //    }

    return ;
}


void EABase::InitPara(const Para &para)
{


    cross_rate = para.cross_rate ;
    field = para.field_map ;
    mutation_rate = para.mutation_rate ;
    pop_size = para.pop_size ;
    total_gen = para.total_gen ;

    double q = 2* acos( 1.0* gRadComm/ ( 2*gRadSens) ) ;
    double overlap = pow( double( gRadSens), 2.0 ) * ( q - sin(q) ) ;
    double c = M_PI * pow( double( gRadSens), 2.0 ) ;

    min_size = ( pow( double( gFieldLength - 1 ), 2.0) - overlap ) / (c - overlap ) ;
}

//void EABase::Start()
//{
//    state = kRunning ;
//}

//void EABase::Pause()
//{
//    state = kPausing ;
//}

//void EABase::Stop()
//{
//    state = kStopping ;
//    Initialize();
//}
