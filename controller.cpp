#include <QDebug>
#include <QGraphicsScene>
#include <QPainter>
#include <QBrush>
#include "controller.h"
#include "dashboard.h"
#include "setdialog.h"


Controller::Controller(QGraphicsScene* dScene,
                       QGraphicsScene *fScene,
                       DashBoard* dBoard ,
                       QObject *parent) :
    diagramScene(dScene),
    fieldScene(fScene),
    dashBoard(dBoard),
    QObject(parent)
{

    worker = new EAWorker ;
    worker->moveToThread( &workerThread );

    state = kStopping ;

    connect( &workerThread, &QThread::finished, worker, &QObject::deleteLater ) ;

    workerThread.start();

    //Graphics related initialized
    diagram = new Diagram ;
    diagramScene->addItem( diagram );

    fieldSimulator = new FieldSimulator;
    fieldScene->addItem( fieldSimulator ) ;

    //Control signals and slots connections
    connect( this, &Controller::NSGA2Signal, worker, &EAWorker::setNSGA2 ) ;
    connect( this, &Controller::MOEADSignal, worker, &EAWorker::setMOEAD ) ;
    connect( this, &Controller::EAStartPauseSignal, worker, &EAWorker::startPauseEA ) ;
    connect( this, &Controller::EAStopSignal, worker, &EAWorker::stopEA ) ;
    connect( this, &Controller::singleRun, worker, &EAWorker::singleRun ) ;


    connect( worker, &EAWorker::updatePiant,
             this, &Controller::setDiagramPoints  );

    //#Connections between controller and widget
    connect( dashBoard, &DashBoard::startPauseEA,
             this, &Controller::startPauseEA ) ;
    connect( dashBoard, &DashBoard::stopEA,
             this, &Controller::stopEA ) ;
    connect( dashBoard, &DashBoard::settingSignal,
             this, &Controller::setting ) ;



    defaultPara() ;//Set the default parameter

    //The setting dialog
    setDialog = new SetDialog( field_len, rad_sens, rad_comm,
                               pop_size, total_gen, mut_rate, cross_rate ) ;
}

Controller::~Controller()
{
    workerThread.quit();
    workerThread.wait();
}

void Controller::setting()
{
    if ( state != kStopping ){

        dashBoard->printLine( "The algorithm is running. Cannot change the parameters now.\n" );
        return ;
    }

    if ( SetDialog::Accepted == setDialog->exec() ){


        field_len = setDialog->getFieldLength() ;
        rad_sens = setDialog->getRadSens() ;
        rad_comm = setDialog->getRadComm() ;
        pop_size = setDialog->getPopSize() ;
        total_gen =  setDialog->getTotalGen();
        cross_rate = setDialog->getCrossRate() ;
        mut_rate = setDialog->getMutRate() ;

        worker->setPara( field_len, rad_sens, rad_comm,
                         pop_size, total_gen, cross_rate, mut_rate );
        dashBoard->printLine("Setting succeed!\n") ;
    }
}

void Controller::stopEA()
{
    if ( state == kStopping )
        return ;

    dashBoard->printLine( tr("EA thread stopping...\n") );
    emit EAStopSignal();

    state = kStopping ;
}

void Controller::startPauseEA()
{

    initialize() ;

    emit EAStartPauseSignal();

    if ( state == kRunning ){

        dashBoard->printLine( tr("EA thread pausing...\n") );
        state = kPausing ;
    }else{

        dashBoard->printLine( tr("EA thread starting...\n") );
        state = kRunning ;
    }

}

void Controller::initialize()
{
    for( int i = 0 ; i < pop_size ; i++){

        DiagramPoint* dp = new DiagramPoint() ;
        diagramPoints.push_back(dp);
        diagramScene->addItem( dp );
    }
}

void Controller::defaultPara()
{

    field_len = 500 ;
    rad_sens = 30 ;
    rad_comm = 30 ;
    pop_size = 100 ;
    total_gen = 2000;
    cross_rate = 0.8 ;
    mut_rate = 0.8 ;

    worker->setPara( field_len, rad_sens, rad_comm,
                     pop_size, total_gen, cross_rate, mut_rate );
}

void Controller::setDiagramPoints( QVector<Indiv> vec, QString info, Indiv best, Indiv worst )
{
    Indiv display = vec[0] ;

    for ( int i = 0 ; i < vec.size() ; i++ ){

        if ( display.converage < vec[i].converage )
            display = vec[i] ;

        diagramPoints[i]->setPoint( vec[i], best, worst ) ;
    }

    fieldSimulator->setIndiv(display);

    diagramScene->update();
    fieldScene->update();

    if ( state == kRunning )
        dashBoard->printLine( info );

    emit singleRun() ;
}

