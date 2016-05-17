#include "Field.h"

int gFieldLength = 500 + 1 ;
int gRadSens = 30 ;
int gRadComm = 30 ;
int gxHECN = 250 ;
int gyHECN = 250 ;


Field::Field( )
{

    field_map = new int*[gFieldLength] ;

    for ( int i = 0 ; i < gFieldLength ; i++ )
        field_map[i] = new int[gFieldLength] ;

    for ( int i = 0 ; i < gFieldLength ; i++)
        for ( int j = 0 ; j < gFieldLength ; j++ )
            field_map[i][j] = 0 ;

}

Field::~Field()
{
    for ( int i = 0 ; i < gFieldLength ; i++)
        delete[] field_map[i] ;

    delete[] field_map ;

}

void Field::SetParameters(int field_length, int rad_sens, int rad_comm)
{
    gFieldLength = field_length+1 ;
    gRadSens = rad_sens ;
    gRadComm = rad_comm ;
    gxHECN = gFieldLength/2 ;
    gyHECN = gFieldLength/2 ;
}

int Field::ConveredPoint()
{
//    int counter = 0 ;

//    for ( int i = 0 ; i < gFieldLength ; i++ )
//        for ( int j = 0 ; j < gFieldLength ; j++ )
//            if ( field_map[i][j] )
//                counter++ ;

//    return counter ;
    return 0;
}

void Field::ClearMap()
{
    for ( int i = 0 ; i < gFieldLength ; i++ )
        for ( int j = 0 ; j < gFieldLength ; j++ )
            field_map[i][j] = 0 ;

    return ;
}

Field::Field(const Field& other)
{
    if ( this != &other ){

        field_map = new int*[gFieldLength] ;

        for ( int i = 0 ; i < gFieldLength ; i++ )
            field_map[i] = new int[gFieldLength] ;

        for ( int i = 0 ; i < gFieldLength ; i++ )
            for ( int j = 0 ; j < gFieldLength ; j++ )
                this->field_map[i][j] = other.field_map[i][j] ;
    }
}

Field& Field::operator=( const Field& other )
{
    if ( this != &other ){

        for ( int i = 0 ; i < gFieldLength ; i++ )
            for ( int j = 0 ; j < gFieldLength ; j++ )
                this->field_map[i][j] = other.field_map[i][j] ;

        return *this ;
    }
}
