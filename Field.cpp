#include "Field.h"

int gFieldLength ;
int gRadSens ;
int gRadComm ;
int gxHECN ;
int gyHECN ;


Field::Field( int len, int r_sens, int r_comm )
{
    gFieldLength = len+1 ;
    gRadSens = r_sens ;
    gRadComm = r_comm ;

    gxHECN = (len+1)/2 ;
    gyHECN = (len+1)/2 ;

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

int Field::ConveredPoint()
{
    int counter = 0 ;

    for ( int i = 0 ; i < gFieldLength ; i++ )
        for ( int j = 0 ; j < gFieldLength ; j++ )
            if ( field_map[i][j] )
                counter++ ;

    return counter ;
}

void Field::ClearMap()
{
    for ( int i = 0 ; i < gFieldLength ; i++ )
        for ( int j = 0 ; j < gFieldLength ; j++ )
            field_map[i][j] = 0 ;

    return ;
}
