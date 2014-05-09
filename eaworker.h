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

    //void setPoints( QVector<Indiv>& vec ) ;
    void updatePiant( QVector<Indiv> vec, QString info ) ;

public slots:
    void startPauseEA() ;
    //void pauseEA() ;
    void stopEA() ;

    void setNSGA2() ;
    void setMOEAD() ;
    void setPara() ;

    void setCache() ;

    void singleRun() ;

    QVector<Indiv> getCache() ;


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
