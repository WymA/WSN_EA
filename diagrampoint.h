#ifndef DIAGRAMPOINT_H
#define DIAGRAMPOINT_H

#include  <QGraphicsItem>
#include "EABase.h"

//class Widget ;

class DiagramPoint : public QGraphicsItem
{

public:

    DiagramPoint();
    QRectF boundingRect() const ;
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0) ;
    QPainterPath shape() const;
    void setPoint( const Indiv& ind ) ;

protected:
    void advance(int step);

private:
    Indiv point ;
    //Widget* mainWidget ;
};

#endif // DIAGRAMPOINT_H
