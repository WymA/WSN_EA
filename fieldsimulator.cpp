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

    vector<XNode> vec ;

    indiv.getVector( vec, indiv.x_var );



    for ( int i = 1 ; i < vec.size() ; i++ ){

        painter->setPen( Qt::black );
        if ( vec[i].parent )
            painter->drawLine( -kPlotSize + vec[i].x_pos , -kPlotSize + vec[i].y_pos ,
                               -kPlotSize + vec[i].parent->x_pos , -kPlotSize + vec[i].parent->y_pos );

        QPainterPath p ;
        p.addEllipse( -kPlotSize + vec[i].x_pos - kSensorSize/2,
                      -kPlotSize + vec[i].y_pos - kSensorSize/2,
                      kSensorSize, kSensorSize);
        painter->fillPath(p, Qt::red  );


    }

    QPainterPath hecn ;
    hecn.addEllipse( -kPlotSize + vec[0].x_pos - kSensorSize/2 ,
            -kPlotSize + vec[0].y_pos  - kSensorSize/2,
            kSensorSize,
            kSensorSize);
    painter->fillPath( hecn, Qt::green  );

    painter->restore();
}


void FieldSimulator::setIndiv( Indiv ind )
{
    indiv = ind ;
}
