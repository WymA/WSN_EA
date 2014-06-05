#ifndef DIAGRAM_H
#define DIAGRAM_H

#include <QGraphicsItem>


#include "EABase.h"


class Diagram: public QGraphicsItem
{
    QVector<Indiv> pareto_front ;
    Indiv best ;
    Indiv worst ;
public:
    Diagram();

    QRectF boundingRect() const ;
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0) ;

    void setFront(QVector<Indiv>& front , const Indiv &best, const Indiv &worst) ;

};

#endif // DIAGRAM_H
