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

#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    layout(new QGridLayout(this))
{
    ui->setupUi(this);


    resize(1280, 640 ) ;

    //Initialize the view and scene
    diagramScene = new QGraphicsScene ;
    diagramView = new QGraphicsView(diagramScene) ;
    fieldScene = new QGraphicsScene ;
    fieldView = new QGraphicsView(fieldScene) ;
    dashBoard = new DashBoard(this) ;
    controller = new Controller( diagramScene, fieldScene ) ;

    //Layout
    layout->addWidget( diagramView, 0, 0, 3, 3 ) ;
    layout->addWidget( dashBoard, 0, 3, 3, 1 );

    //DashBoard* t = new DashBoard;
    layout->addWidget( fieldView, 0, 4, 3, 3 );

    //#Connections between controller and widget
    connect( dashBoard, &DashBoard::startPauseEA,
             controller, &Controller::startPauseEA ) ;

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
    diagramScene->setSceneRect( -length(),
                               -length(),
                               2*length() ,
                               2*length());
}
