#ifndef DIAGRAMPOINT_H
#define DIAGRAMPOINT_H

#include <QGraphicsObject>
#include "EABase.h"

class DiagramPoint : public QGraphicsObject
{
    Q_OBJECT
public:
    DiagramPoint();
    QRectF boundingRect() const ;
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0) ;
    QPainterPath shape() const;
    void setPoint(const Indiv& ind ,const Indiv& best, const Indiv& worst) ;

signals:
    void sendIndiv( Indiv ind ) ;

protected:
    void advance(int step);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event) ;

private:
    Indiv point ;
    bool is_selected ;

    qreal x ;
    qreal y ;
    //Widget* mainWidget ;
};

#endif // DIAGRAMPOINT_H
