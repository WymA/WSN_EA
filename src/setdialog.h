#ifndef SETDIALOG_H
#define SETDIALOG_H
#include <QDialog>
#include "Constants.h"

class QSpinBox;
class QComboBox;

class SetDialog : public QDialog
{
    Q_OBJECT
public:
    SetDialog(int f_length, int r_sens,  int r_comm,
               int pop, int t_gen, double m_rate, double c_rate, kMOEA ea);
    ~SetDialog() ;

private:

    int field_length;
    int rad_sens;
    int rad_comm;

    int pop_size ;
    int total_gen ;
    double mut_rate ;
    double cross_rate ;

    kMOEA EA;

    QSpinBox* inFieldLength ;
    QSpinBox* inRadSens ;
    QSpinBox* inRadComm ;
    QSpinBox* inPopSize ;
    QSpinBox* inTotalGen ;
    QSpinBox* inCrossRate ;
    QSpinBox* inMutRate ;

    QComboBox* inMOEA ;

    void setData() ;

public:

    inline int getFieldLength() const { return field_length; }
    inline int getRadSens() const { return rad_sens; }
    inline int getRadComm() const { return rad_comm; }

    inline int getPopSize() const { return pop_size; }
    inline int getTotalGen() const { return total_gen; }
    inline double getMutRate() const { return mut_rate; }
    inline double getCrossRate() const { return cross_rate; }
    inline kMOEA getEA() const { return EA; }

};

#endif // SETDIALOG_H
