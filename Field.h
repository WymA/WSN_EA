#ifndef FIELD_H
#define FIELD_H

extern int gFieldLength ;
extern int gRadSens ;
extern int gRadComm ;
extern int gxHECN ;
extern int gyHECN ;

void SetParameters(int field_length, int rad_sens, int rad_comm) ;


class Field
{
 public:
  
  int** field_map ;

 public:
  
  Field() ;
  Field(const Field& other) ;
  ~Field() ;

  int ConveredPoint() ;
  void ClearMap() ;

  Field& operator=( const Field& other ) ;
  
  static void SetParameters( int field_length, int rad_sens, int rad_comm ) ;
};

#endif
