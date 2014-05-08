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

    painter->drawPath( shape() );

    painter->restore();
}


void DiagramPoint::advance(int step)
{
    if (!step) return ;

    return ;
}

void DiagramPoint::setPoint( const Indiv& ind )
{
    point = ind ;

    qreal x =  2*kPlotSize*(1.0 - 1.0/(point.y_var[kObjNodes] /*- point.penalty - 300 */)) - kPlotSize ;
    qreal y =  kPlotSize  - 2*kPlotSize*(1.0 - 1.0/(point.y_var[kObjEnergy]/* - point.penalty - 5.0 */)) ;

    //qDebug()<< point.y_var[kObjNodes] - point.penalty<<' '<< point.y_var[kObjEnergy] - point.penalty ;

    setPos( x, y ) ;
}
