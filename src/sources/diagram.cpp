#include <QPainter>
#include "diagram.h"
#include "Constants.h"


//#include "widget.h"




Diagram::Diagram()
{
}


QRectF Diagram::boundingRect() const
{

}

void Diagram::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget )
{
    painter->save();

    painter->setPen( Qt::red );


    qreal _X = 2*kPlotSize/( worst.y_var[kObjNodes] - best.y_var[kObjNodes] + 10) ;
    qreal _Y = 2*kPlotSize/( worst.y_var[kObjEnergy] - best.y_var[kObjEnergy] + 10) ;

    for ( int i = 1 ; i < pareto_front.size() ; i++ )
        painter->drawLine( _X*(pareto_front[i].y_var[kObjNodes]- best.y_var[kObjNodes] ) - kPlotSize + 10 ,
                           -_Y *( pareto_front[i].y_var[kObjEnergy] - best.y_var[kObjEnergy] ) + kPlotSize - 10,
                           _X*(pareto_front[i-1].y_var[kObjNodes]- best.y_var[kObjNodes] ) - kPlotSize + 10 ,
                -_Y *( pareto_front[i-1].y_var[kObjEnergy] - best.y_var[kObjEnergy] ) + kPlotSize - 10 );

    painter->setPen( Qt::black );

    qreal len = kPlotSize ;
    QLineF ry( mapFromScene(-len, -len),
               mapFromScene(-len,  len )) ;
    QLineF rx( mapFromScene(-len,  len),
               mapFromScene(len,  len )) ;


    painter->setPen(QPen(Qt::black, 3)) ;

    painter->drawLine(ry);
    painter->drawLine(rx);

    painter->drawText( -len-10, len+10, "O" );
    painter->drawText( -len-10, -len-10, "Energy" );
    painter->drawText( len -50, len+20, "Nodes" );

    painter->restore();
}

void Diagram::setFront( QVector<Indiv>& front, const Indiv& best, const Indiv& worst )
{
    pareto_front = front ;

    this->best = best ;
    this->worst = worst ;

}
