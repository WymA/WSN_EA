#include <QVector>
#include <QPainter>
#include "Constants.h"
#include "fieldsimulator.h"


FieldSimulator::FieldSimulator()
{

    for ( int i = 0 ; i != 510 ; i+=10 ){

        QPointF p1( -kPlotSize + i,  -kPlotSize ), p2( -kPlotSize + i,  kPlotSize ) ;
        QLineF line( mapFromScene(p1), mapFromScene(p2) ) ;
        bgh.push_back( line );
    }

    for ( int i = 0 ; i != 510 ; i+=10 ){

        QPointF p1( -kPlotSize ,  -kPlotSize+ i ), p2( kPlotSize,  -kPlotSize + i ) ;
        QLineF line( mapFromScene(p1), mapFromScene(p2) ) ;
        bgv.push_back( line );
    }

}


QRectF FieldSimulator::boundingRect() const
{
    QRectF tmp( -kPlotSize, -kPlotSize, 2*kPlotSize, 2*kPlotSize ) ;
    return tmp ;
}


void FieldSimulator::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget )
{
    painter->save();

    //painter->setPen( Qt::d);
    painter->setPen( Qt::gray );

    painter->drawLines(bgh);
    painter->drawLines(bgv);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen( Qt::red );

//    for ( int i = 0 ; i < indiv.x_var.size() ; i++ ){

//        QPainterPath p ;
//        p.addEllipse( -kPlotSize + indiv.x_var[i].x_pos, -kPlotSize + indiv.x_var[i].y_pos, 6.0, 6.0);
//        painter->fillPath(p, Qt::red  );

//        painter->setPen( Qt::black );
//        for ( vector<int>::iterator it = indiv.x_var[i].neigh.begin() ; it != indiv.x_var[i].neigh.end() ; it++ )
//            painter->drawLine( -kPlotSize + indiv.x_var[i].x_pos, -kPlotSize + indiv.x_var[i].y_pos ,
//                               -kPlotSize + indiv.x_var[*it].x_pos, -kPlotSize + indiv.x_var[*it].y_pos );
//    }

    painter->restore();
}


void FieldSimulator::setIndiv( Indiv ind )
{
    indiv = ind ;
}
