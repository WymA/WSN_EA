#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QThread>
#include <QVector>
#include "Constants.h"
#include "diagram.h"
#include "diagrampoint.h"
#include "eaworker.h"
#include "fieldsimulator.h"

class SetDialog ;
class QGraphicsScene ;
class DashBoard ;

class Controller : public QObject
{
    Q_OBJECT

public:
    explicit Controller(QGraphicsScene* dScene , QGraphicsScene* fScene, DashBoard *dBoard, QObject *parent = 0 );
    ~Controller() ;

    QVector<Indiv> getCaches() ;
signals:

    void SetEA( kMOEA ea ) ;
    void EAStartPauseSignal() ;
    void EAStopSignal() ;

    //void setPoints( QVector<Indiv>& vec ) ;
    void updatePaint() ;
    void singleRun() ;

public slots:
    void startPauseEA() ;
    void stopEA() ;
    void setDiagramPoints(QVector<Indiv> vec, QString info, Indiv best, Indiv worst) ;
    void defaultPara() ;
    void initialize() ;
    void setting() ;
    void out2File() ;
    void pop2Front( QVector<Indiv>& vec ) ;

    void change2Coverage() ;
    void change2Nodes() ;
    void change2Energy() ;

    void setSimuIndiv(Indiv ind ) ;

private:
    QThread workerThread ;
    EAWorker* worker ;
    kMOEA moea ;
    kDisplay display ;
    Indiv bestCoverage ;
    Indiv bestNodes ;
    Indiv bestEnergy ;

    QVector<Indiv> pareto_front ;

    //Graphics items
    QGraphicsScene* diagramScene ;
    QGraphicsScene* fieldScene ;
    DashBoard* dashBoard ;
    SetDialog* setDialog ;

    Diagram* diagram ;
    QVector<DiagramPoint*> diagramPoints ;
    FieldSimulator* fieldSimulator ;

private:
    //Parameters
    int field_len ;
    int rad_sens ;
    int rad_comm ;
    int pop_size ;
    int total_gen ;
    double cross_rate ;
    double mut_rate ;

};

#endif // CONTROLLER_H
