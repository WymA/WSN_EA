#include <QDebug>
#include <QGraphicsScene>
#include <QPainter>
#include <QFile>
#include <QBrush>
#include "controller.h"
#include "dashboard.h"
#include "setdialog.h"


bool CompareForPareto( const Indiv& ind1, const Indiv& ind2 )
{
    return ind1.y_var[kObjNodes] < ind2.y_var[kObjNodes] ;
}


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

    moea = kMOEAD ;
    display = kBestCoverage ;

    connect( &workerThread, &QThread::finished, worker, &QObject::deleteLater ) ;

    workerThread.start();

    //Graphics related initialized
    diagram = new Diagram ;
    diagramScene->addItem( diagram );

    fieldSimulator = new FieldSimulator;
    fieldScene->addItem( fieldSimulator ) ;

    //Control signals and slots connections
    connect( this, &Controller::SetEA, worker, &EAWorker::setEA ) ;
    connect( this, &Controller::EAStartPauseSignal, worker, &EAWorker::startPauseEA ) ;
    connect( this, &Controller::EAStopSignal, worker, &EAWorker::stopEA ) ;
    connect( this, &Controller::singleRun, worker, &EAWorker::singleRun ) ;


    connect( worker, &EAWorker::updatePaint,
             this, &Controller::setDiagramPoints  );

    //#Connections between controller and widget
    connect( dashBoard, &DashBoard::startPauseEA,
             this, &Controller::startPauseEA ) ;
    connect( dashBoard, &DashBoard::stopEA,
             this, &Controller::stopEA ) ;
    connect( dashBoard, &DashBoard::settingSignal,
             this, &Controller::setting ) ;
    connect( dashBoard, &DashBoard::outputSignal,
             this, &Controller::out2File ) ;

    connect( dashBoard, &DashBoard::displayCoverage,
             this, &Controller::change2Coverage ) ;
    connect( dashBoard, &DashBoard::displayEnergy,
             this, &Controller::change2Energy ) ;
    connect( dashBoard, &DashBoard::displayNodes,
             this, &Controller::change2Nodes ) ;



    defaultPara() ;//Set the default parameter

    //The setting dialog
    setDialog = new SetDialog( field_len, rad_sens, rad_comm,
                               pop_size, total_gen, mut_rate, cross_rate, moea ) ;
}

Controller::~Controller()
{
    workerThread.quit();
    workerThread.wait();
}

void Controller::setting()
{
    if ( worker->getState() != kStopping ){

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
        moea = setDialog->getEA() ;

        worker->setPara( field_len, rad_sens, rad_comm,
                         pop_size, total_gen, cross_rate, mut_rate );

        emit SetEA( moea ) ;

        dashBoard->printLine("Setting succeed!\n") ;
    }
}

void Controller::out2File()
{
    QFile data("pareto_front.log");
    if (data.open(QFile::WriteOnly | QIODevice::Truncate)) {

        QTextStream out(&data);

        for ( int i = 0 ; i < pareto_front.size() ; i++ )
            out << pareto_front[i].y_var[kObjNodes] - pareto_front[i].penalty<< "\t"
                << pareto_front[i].y_var[kObjEnergy] - pareto_front[i].penalty<< "\t"
                   << pareto_front[i].penalty<<"\r\n";
    }
}

void Controller::stopEA()
{
    if ( worker->getState() == kStopping )
        return ;

    dashBoard->printLine( tr("EA thread stopping...\n") );
    emit EAStopSignal();
}

void Controller::startPauseEA()
{

    initialize() ;

    emit EAStartPauseSignal();

    if (  worker->getState() == kRunning ){

        dashBoard->printLine( tr("EA thread pausing...\n") );
    }else{

        dashBoard->printLine( tr("EA thread starting...\n") );
    }

}

void Controller::initialize()
{
    for( int i = 0 ; i < pop_size ; i++){

        DiagramPoint* dp = new DiagramPoint() ;
        diagramPoints.push_back(dp);
        diagramScene->addItem( dp );
    }

    for ( int i = 0 ; i < diagramPoints.size() ; i++ )
        connect( diagramPoints[i], &DiagramPoint::sendIndiv,
                 this, &Controller::setSimuIndiv ) ;
}

void Controller::setSimuIndiv( Indiv ind )
{
    qDebug() << "----------------" ;

    fieldSimulator->setIndiv( ind );
    fieldScene->update();
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

void Controller::pop2Front( QVector<Indiv>& vec )
{
    QVector<int> dominated = QVector<int>( vec.size(), 0 ) ;

    for ( int i = 0 ; i < vec.size() ; i++ ){

        for ( int j = i+1 ; j < vec.size() ; j++ ){

            TCompare res = Compare( vec[i], vec[j] ) ;

            if ( kParetoDominating == res )
                dominated[j]++ ;
            if ( kParetoDominated == res )
                dominated[i]++ ;
        }
    }

    pareto_front.clear();

    bestCoverage = vec[0] ;
    bestNodes = vec[0] ;
    bestEnergy = vec[0] ;

    for ( int i = 0 ; i < vec.size() ; i++ ){

        if ( bestCoverage.coverage < vec[i].coverage )
            bestCoverage = vec[i] ;
        if ( bestNodes.y_var[kObjNodes] > vec[i].y_var[kObjNodes] )
            bestNodes = vec[i] ;
        if ( bestEnergy.y_var[kObjEnergy] > vec[i].y_var[kObjEnergy] )
            bestEnergy = vec[i] ;

        if ( !dominated[i] )
            pareto_front.push_back(vec[i]);
    }

    sort( pareto_front.begin(), pareto_front.end(), CompareForPareto) ;

    dominated.clear();
}

void Controller::setDiagramPoints( QVector<Indiv> vec, QString info, Indiv best, Indiv worst )
{
    pop2Front( vec );

    diagram->setFront( pareto_front, best, worst );

    for ( int i = 0 ; i < vec.size() ; i++ )
        diagramPoints[i]->setPoint( vec[i], best, worst ) ;

    switch ( display )
    {
    case kBestCoverage:
        fieldSimulator->setIndiv(bestCoverage);
        break ;
    case kBestNodes:
        fieldSimulator->setIndiv(bestNodes);
        break ;
    case kBestEnergy:
        fieldSimulator->setIndiv(bestEnergy);
        break ;
    }

    diagramScene->update();
    fieldScene->update();

    if (  worker->getState() == kRunning )
        dashBoard->printLine( info );

    emit singleRun() ;
}

void Controller::change2Coverage()
{
    display = kBestCoverage ;

    if ( worker->getState() != kRunning ){

        fieldSimulator->setIndiv(bestCoverage);
        fieldScene->update();
    }
}
void Controller::change2Nodes()
{
    display = kBestNodes ;

    if ( worker->getState() != kRunning ){

        fieldSimulator->setIndiv(bestNodes);
        fieldScene->update();
    }
}
void Controller::change2Energy()
{
    display = kBestEnergy;

    if ( worker->getState() != kRunning ){

        fieldSimulator->setIndiv(bestEnergy);
        fieldScene->update();
    }
}
