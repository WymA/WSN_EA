#ifndef DIAGRAM_H
#define DIAGRAM_H

#include  <QGraphicsItem>



class Diagram: public QGraphicsItem
{
public:
    Diagram();

    QRectF boundingRect() const ;
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0) ;

};

#endif // DIAGRAM_H
