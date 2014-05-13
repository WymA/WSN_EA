#ifndef EAWORKER_H
#define EAWORKER_H

#include <QObject>
#include <QVector>
#include <QThreadStorage>
#include <QMutex>
#include "Constants.h"
#include "EABase.h"
#include "NSGA2.h"
#include "MOEAD.h"


class EAWorker : public QObject
{
    Q_OBJECT
public:
    explicit EAWorker(QObject *parent = 0);

signals:

    void updatePiant( QVector<Indiv> vec, QString info, Indiv best, Indiv worst ) ;

public slots:
    void startPauseEA() ;
    //void pauseEA() ;
    void stopEA() ;

    void setNSGA2() ;
    void setMOEAD() ;
    void setPara( int f_len, int r_sens, int r_comm,
                  int p_size, int t_gen, double c_rate, double m_rate ) ;

    void setCache() ;
    void singleRun() ;

    QVector<Indiv> getCache() ;

    //kRunningState getState() { return state; }

private:
    MOEAD moead ;
    NSGA2 nsga2 ;
    EABase* ea ;
    Field* field ;
    Para* para ;

    QMutex mutex ;
    kRunningState state ;

    QVector<Indiv> caches ;
};

#endif // EAWORKER_H
