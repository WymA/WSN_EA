#include <QPainter>
#include <QDebug>

#include "Constants.h"
#include "diagrampoint.h"



DiagramPoint::DiagramPoint()
{
    setPos( -1000, -1000 ) ;
}


QRectF DiagramPoint::boundingRect() const
{
    QRectF bound = QRectF(mapFromScene(QPointF(-kPointSize, -kPointSize)),
                                       mapFromScene(QPointF(kPointSize, kPointSize))) ;

    return bound ;
}

QPainterPath DiagramPoint::shape() const
{
    QPainterPath p;
    p.addEllipse( QPointF( 0, 0 ), kPointSize, kPointSize);
    return p;
}

void DiagramPoint::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget )
{
    painter->save();

    painter->setRenderHint(QPainter::Antialiasing);
    painter->drawPath( shape() );

    painter->restore();
}


void DiagramPoint::advance(int step)
{
    if (!step) return ;

    return ;
}

void DiagramPoint::setPoint( const Indiv& ind, const Indiv& best, const Indiv& worst )
{
    point = ind ;

    qreal _X = worst.y_var[kObjNodes] - best.y_var[kObjNodes] + 5;
    qreal _Y = worst.y_var[kObjEnergy] - best.y_var[kObjEnergy] + 5 ;

    qreal x =  ( 2*kPlotSize / _X )*( point.y_var[kObjNodes] - best.y_var[kObjNodes] + 5)  - kPlotSize ;
    qreal y =  -( 2*kPlotSize / _Y )*( point.y_var[kObjEnergy] - best.y_var[kObjEnergy] + 5) + kPlotSize ;

    setPos( x, y ) ;
}
