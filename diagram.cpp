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
    qreal len = kPlotSize ;

    QLineF ry( mapFromScene(-len, -len),
                    mapFromScene(-len,  len )) ;
    QLineF rx( mapFromScene(-len,  len),
                     mapFromScene(len,  len )) ;

    painter->drawLine(ry);
    painter->drawLine(rx);


    painter->drawText( -len-10, len+10, "origin");

//    diagramScene->addText(tr("origin"))->setPos( -length()-10, length()+10 );
//    diagramScene->addText(tr("number of nodes"))->setPos( length()-100, length()+10 );
//    diagramScene->addText(tr("energy depletion"))->setPos( -length()-10, -length()-30 );
}

