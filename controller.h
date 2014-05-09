#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QThread>
#include <QVector>
#include "diagram.h"
#include "diagrampoint.h"
#include "eaworker.h"
#include "fieldsimulator.h"

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
    void paraSignal() ;
    void NSGA2Signal() ;
    void MOEADSignal() ;

    void EAStartPauseSignal() ;
    void EAStopSignal() ;

    //void setPoints( QVector<Indiv>& vec ) ;
    void updatePaint() ;
    void singleRun() ;

public slots:
    void startPauseEA() ;
    void setDiagramPoints(QVector<Indiv> vec, QString info) ;
    void setPara() ;
    void initialize() ;

private:
    QThread workerThread ;
    EAWorker* worker ;
    Para* para ;

    //Graphics items
    QGraphicsScene* diagramScene ;
    QGraphicsScene* fieldScene ;
    DashBoard* dashBoard ;

    Diagram* diagram ;
    QVector<DiagramPoint*> diagramPoints ;
    FieldSimulator* fieldSimulator ;

};

#endif // CONTROLLER_H
