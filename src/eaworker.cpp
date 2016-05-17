#include <QMutexLocker>
#include <QDebug>
#include <QThread>
//#include <QMetaType>

#include "eaworker.h"



EAWorker::EAWorker(QObject *parent) :
    QObject(parent),
    ea(0)
{
    state = kStopping ;
    moea = kMOEAD ;

    qRegisterMetaType<QVector<Indiv> >("QVector<Indiv> ") ;
    qRegisterMetaType<Indiv>("Indiv") ;
    qRegisterMetaType<kMOEA>("kMOEA") ;

}


void EAWorker::setCache()
{
    QMutexLocker locker(&mutex) ;

    if ( !caches.empty() )
        caches.clear();

    for ( int i = 0 ; i < ea->getSize() ; i++ )
        caches.push_back( ea->getIndiv(i) );
}

QVector<Indiv> EAWorker::getCache()
{
    return caches ;
}

void EAWorker::setPara( int f_len,
                        int r_sens,
                        int r_comm,
                        int p_size,
                        int t_gen,
                        double c_rate,
                        double m_rate )
{

    Field::SetParameters( f_len, r_sens, r_comm ) ;
    field = new Field() ;
    para = new Para( p_size, t_gen, c_rate, m_rate ) ;
}


void EAWorker::setEA( kMOEA ea )
{
    moea = ea ;
}

void EAWorker::setNSGA2()
{
    if ( state == kStopping ){

        if ( ea )
            delete ea ;

        ea = new NSGA2( *para ) ;
    }

}

void EAWorker::setMOEAD()
{

    if ( state == kStopping ){

        if ( ea )
            delete ea ;

        ea = new MOEAD(*para) ;
    }
}


void EAWorker::singleRun()
{
    if ( ea->getCurGen() > para->total_gen )
        state = kStopping ;

    if ( state != kRunning )
        return ;

    QString info = ea->SingleRun();
    setCache() ;

    emit updatePaint( getCache(), info,
                      ea->getBestInd(), ea->getWorstInd() );


}

void EAWorker::startPauseEA()
{

    if ( state == kStopping ) {

        if ( moea == kMOEAD )
            setMOEAD();
        if ( moea == kNSGA2 )
            setNSGA2();
        ea->Initialize();

        state = kRunning ;
        singleRun();
    }else if ( state == kPausing){

        state = kRunning ;
        singleRun() ;

    }else if ( state == kRunning ){

        state = kPausing ;
    }
}

void EAWorker::stopEA()
{
    state = kStopping ;
}

