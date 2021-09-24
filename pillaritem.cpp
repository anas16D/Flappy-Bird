#include "pillaritem.h"

pillarItem::pillarItem() : topPillar(new QGraphicsPixmapItem(QPixmap(":/images/pipe.png"))),
                           bottomPillar(new QGraphicsPixmapItem(QPixmap(":/images/pipe.png")))
{
    topPillar->setPos(QPointF(0,0) - QPointF(topPillar->boundingRect().width()/2, topPillar->boundingRect().height() + 60));
    bottomPillar->setPos(QPointF(0,0) + QPointF(-bottomPillar->boundingRect().width()/2, 60));

    addToGroup(topPillar);
    addToGroup(bottomPillar);

}
