#ifndef FIELD_H
#define FIELD_H

extern int gFieldLength ;
extern int gRadSens ;
extern int gRadComm ;
extern int gxHECN ;
extern int gyHECN ;

class Field
{
 public:
  
  int** field_map ;

 public:
  
  Field( int len, int r_sens, int r_comm ) ;
  ~Field() ;

  int ConveredPoint() ;
  void ClearMap() ;
  
};

#endif
