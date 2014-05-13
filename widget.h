#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QVector>
//#include "diagrampoint.h"


namespace Ui {
class Widget;
}


class QGraphicsScene;
class QGraphicsView ;
class QGridLayout ;
class DashBoard ;
//class Diagram ;
class Controller ;
//class Diagram;

class Widget : public QWidget
{
    Q_OBJECT


public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    int length()  ;

signals:


public slots:
    //void setDiagramPoints() ;

private:
    Ui::Widget *ui;
    QGridLayout* layout ;

    QGraphicsScene* diagramScene ;
    QGraphicsView* diagramView ;

    QGraphicsScene* fieldScene ;
    QGraphicsView* fieldView ;

    Controller* controller ;
    DashBoard* dashBoard ;

protected:
    void paintEvent(QPaintEvent * event) ;
    void resizeEvent(QResizeEvent * event) ;

private:
    //Para* para ;
    //void initialize() ;
};




#endif // WIDGET_H
