#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGridLayout>
#include <QPushButton>
#include <QGraphicsItem>
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <QDebug>

#include "controller.h"
#include "dashboard.h"
#include "Constants.h"
#include "EABase.h"
#include "diagram.h"
#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    layout(new QGridLayout(this))
{
    ui->setupUi(this);

    this->setWindowTitle( "Wireless Sensor Network Layout Optimization System" );

    resize(1400, 640 ) ;

    //Initialize the view and scene
    diagramScene = new QGraphicsScene ;
    diagramView = new QGraphicsView(diagramScene) ;
    fieldScene = new QGraphicsScene ;
    fieldView = new QGraphicsView(fieldScene) ;
    dashBoard = new DashBoard(this) ;
    controller = new Controller( diagramScene, fieldScene, dashBoard ) ;

    //Layout
    layout->addWidget( diagramView, 0, 0, 4, 4 ) ;
    layout->addWidget( dashBoard, 0, 4, 4, 2 );

    //DashBoard* t = new DashBoard;
    layout->addWidget( fieldView, 0, 6, 4, 4 );


}

Widget::~Widget()
{
    diagramScene->clear();
    delete diagramView ;
    delete diagramScene ;
    delete controller ;
    delete layout ;
    delete fieldScene ;
    delete fieldView ;
    delete dashBoard ;
    delete ui;
}


int Widget::length()
{
    return this->height()/2-100 ;
}


void Widget::paintEvent(QPaintEvent * event)
{
    //TODO
}

void Widget::resizeEvent(QResizeEvent * event)
{
    diagramScene->setSceneRect( -kPlotSize,
                               -kPlotSize,
                               2*kPlotSize ,
                               2*kPlotSize);
}
