#include <QMutexLocker>
#include <QDebug>
#include <QThread>
//#include <QMetaType>

#include "eaworker.h"



EAWorker::EAWorker(QObject *parent) :
    QObject(parent),
    ea(0)
{
    //timer.start( 1000/3 );
    state = kStopping ;

    setPara() ;
    qRegisterMetaType<QVector<Indiv> >("QVector<Indiv> ") ;
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

void EAWorker::setPara()
{
    field = new Field( 500, 30, 30 ) ;
    para = new Para(field, 100, 1000, 0.8, 0.8 ) ;
}

void EAWorker::setNSGA2()
{
    if ( state == kStopping ){

        if ( ea )
            delete ea ;

        ea = new NSGA2(*para) ;
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
    if ( ( ea->getCurGen() > para->total_gen) || state != kRunning )
        return ;

    ea->SingleRun();
    setCache() ;

    emit updatePiant( getCache() );
}

void EAWorker::startPauseEA()
{

    if ( state == kStopping ) {

        setMOEAD();
        state = kRunning ;

        ea->Initialize();
        //ea->Execute() ;
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

