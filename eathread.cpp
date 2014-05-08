#include "NSGA2.h"
#include "MOEAD.h"
#include "controller.h"

#include "eathread.h"
#include <QDebug>

EAThread::EAThread(QObject *parent) :
    QThread(parent)
{
    controller = NULL ;
    ea = NULL;
}

EAThread::~EAThread()
{
    delete ea ;
    delete controller ;
}


void EAThread::run()
{
    Field field( 500, 30, 30 ) ;
    Para par( &field, 100, 3000, 0.8, 0.8 ) ;

    ea->Execute(par, controller ) ;

}

void EAThread::set2NSGA2()
{

}
