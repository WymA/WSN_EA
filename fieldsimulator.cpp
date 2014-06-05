#include <QVector>
#include <QPainter>
#include "Constants.h"
#include "fieldsimulator.h"


FieldSimulator::FieldSimulator()
{
    XNode hecn( gxHECN, gyHECN) ;
    indiv.x_var.push_back(hecn);

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



    painter->setRenderHint(QPainter::Antialiasing);


    painter->setPen( Qt::black);
    QPainterPath hecnMark ;
    hecnMark.addEllipse( -kPlotSize + 30 - kSensorSize/2 ,
                         kPlotSize + 20  - kSensorSize/2,
                         kSensorSize,
                         kSensorSize);
    painter->fillPath( hecnMark, Qt::green  );
    painter->drawText( -kPlotSize  ,
                       kPlotSize + 23 ,
                       "HECN");
    QPainterPath nodeMark ;
    nodeMark.addEllipse( -kPlotSize + 30 - kSensorSize/2 ,
                         kPlotSize + 40  - kSensorSize/2,
                         kSensorSize,
                         kSensorSize);
    painter->fillPath( nodeMark, Qt::red  );
    painter->drawText( -kPlotSize  ,
                       kPlotSize + 43 ,
                       "node");



    for ( int i = 0 ; i < gFieldLength ; i++ )
        for ( int j = 0 ; j < gFieldLength ;  j++ ){

            if ( indiv.field.field_map[i][j] /*== 1*/ ){

                painter->setPen( Qt::yellow );
                painter->drawPoint( -kPlotSize+j, -kPlotSize+i);
            }
//            if ( indiv.field.field_map[i][j] == 2 ){

//                painter->setPen( Qt::green );
//                painter->drawPoint( -kPlotSize+i, -kPlotSize+j);
//            }
//            if ( indiv.field.field_map[i][j] > 2 ){

//                painter->setPen( Qt::blue );
//                painter->drawPoint( -kPlotSize+i, -kPlotSize+j);
//            }
        }


    painter->setPen( Qt::gray );

    painter->drawLines(bgh);
    painter->drawLines(bgv);


    painter->setPen( Qt::red );

    for ( int i = 1 ; i < indiv.x_var.size() ; i++ ){

        painter->setPen( Qt::black );

        QPainterPath p ;
        p.addEllipse( -kPlotSize + indiv.x_var[i].x_pos - kSensorSize/2,
                      -kPlotSize + indiv.x_var[i].y_pos - kSensorSize/2,
                      kSensorSize, kSensorSize);
        painter->fillPath(p, Qt::red  );

        painter->setPen( Qt::black );

        for ( int n = 0 ; n < indiv.x_var[i].neigh.size() ; n++ )
            painter->drawLine( -kPlotSize + indiv.x_var[i].x_pos,
                               -kPlotSize + indiv.x_var[i].y_pos ,
                               -kPlotSize + indiv.x_var[indiv.x_var[i].neigh[n]].x_pos,
                               -kPlotSize + indiv.x_var[indiv.x_var[i].neigh[n]].y_pos);
    }


    QPainterPath hecn ;
    hecn.addEllipse( -kPlotSize + indiv.x_var[0].x_pos - kSensorSize/2 ,
            -kPlotSize + indiv.x_var[0].y_pos  - kSensorSize/2,
            kSensorSize,
            kSensorSize);
    painter->fillPath( hecn, Qt::green  );



    painter->restore();
}


void FieldSimulator::setIndiv( Indiv ind )
{
    indiv = ind ;
}
