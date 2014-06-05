#include <QPainter>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include "Constants.h"
#include "diagrampoint.h"

DiagramPoint::DiagramPoint()
{
    setPos( -1000, -1000 ) ;

}

QRectF DiagramPoint::boundingRect() const
{
    QRectF bound = QRectF(mapFromScene(QPointF(x-kPointSize*2, y-kPointSize*2)),
                          mapFromScene(QPointF(x+kPointSize*2, y+kPointSize*2))) ;

    return bound ;
}

QPainterPath DiagramPoint::shape() const
{
    QPainterPath p;
    p.addEllipse( QPointF( x, y ), kPointSize, kPointSize);
    return p;
}

void DiagramPoint::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget )
{
    painter->save();

    painter->setRenderHint(QPainter::Antialiasing);
    painter->drawPath( shape() );

    painter->restore();
}

void DiagramPoint::mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event)
{

    emit sendIndiv( point );
}


void DiagramPoint::advance(int step)
{
    if (!step) return ;

    return ;
}

void DiagramPoint::setPoint( const Indiv& ind, const Indiv& best, const Indiv& worst )
{
    setPos( 0 , 0 );

    point = ind ;

    qreal _X = worst.y_var[kObjNodes] - best.y_var[kObjNodes] + 10 ;
    qreal _Y = worst.y_var[kObjEnergy] - best.y_var[kObjEnergy] + 10 ;

    x =  ( 2*kPlotSize / _X )*( point.y_var[kObjNodes] - best.y_var[kObjNodes] )  - kPlotSize + 10 ;
    y =  -( 2*kPlotSize / _Y )*( point.y_var[kObjEnergy] - best.y_var[kObjEnergy] ) + kPlotSize - 10 ;
}
