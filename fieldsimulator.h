#ifndef FIELDSIMULATOR_H
#define FIELDSIMULATOR_H

#include <QGraphicsItem>
#include <QVector>
#include <QLineF>
#include "EABase.h"

class FieldSimulator: public QGraphicsItem
{
public:
    FieldSimulator( );

    QRectF boundingRect() const ;
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0) ;

    void setIndiv(Indiv ind ) ;
private:
    Indiv indiv ;
    QVector<QLineF> bgh, bgv;
    //int index;
};

#endif // FIELDSIMULATOR_H
