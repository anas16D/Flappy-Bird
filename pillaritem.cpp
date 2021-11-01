#include "pillaritem.h"
#include <QRandomGenerator>
#include <QGraphicsScene>
#include <QDebug>
#include "scene.h"
#include "birditem.h"


PillarItem::PillarItem(int durationOfPillar) : topPillar(new QGraphicsPixmapItem(QPixmap(":/images/pipe3.png"))),
                           bottomPillar(new QGraphicsPixmapItem(QPixmap(":/images/pipe3.png"))), sc(0)
{




    topPillar->setPos(QPointF(0,0) - QPointF(topPillar->boundingRect().width()/2, topPillar->boundingRect().height() + 60) );
    bottomPillar->setPos(QPointF(0,0) + QPointF(-bottomPillar->boundingRect().width()/2, 10));

    topPillar->setTransformOriginPoint(topPillar->boundingRect().width()/2, topPillar->boundingRect().height()-190);
    topPillar->setRotation(180);

    addToGroup(topPillar);
    addToGroup(bottomPillar);
//    topPillar->setScale(-0.6);
//    bottomPillar->setScale(-0.95);

    yPos = QRandomGenerator::global()->bounded(50 + durationOfPillar/10);
    int xRandomizer = QRandomGenerator::global()->bounded(180);
    setPos(QPoint(500 , yPos));


    xAnimation = new QPropertyAnimation(this, "x", this);
    xAnimation->setStartValue(470);
    xAnimation->setEndValue(-470);
    xAnimation->setEasingCurve(QEasingCurve::Linear);
    xAnimation->setDuration(1600 - durationOfPillar);

    connect(xAnimation, &QPropertyAnimation::finished, [=](){
        qDebug() << "Animation finished";
       scene()->removeItem(this);
       delete this;
    });

    xAnimation->start();








}

PillarItem::~PillarItem()
{
    qDebug() << "Pillar Item Deleted";
    delete topPillar;
    delete bottomPillar;

}

qreal PillarItem::x() const
{
    return m_x;
}

void PillarItem::freezePillars()
{
    xAnimation->stop();
}

void PillarItem::setX(qreal x)
{
    m_x   = x;
    qDebug() << "X: " << x;


    if(collided())
    {
        emit gameOver();
    }
    setPos(QPointF(0,0) + QPointF(x, yPos));
}

bool PillarItem::collided()
{
    QList<QGraphicsItem*> collidingItems;

    collidingItems.append(topPillar->collidingItems());
    collidingItems.append(bottomPillar->collidingItems());

    foreach(QGraphicsItem *item, collidingItems)
    {
        BirdItem *birdItem = dynamic_cast<BirdItem*>(item);

        if(birdItem)
        {
            return true;
        }
    }

    return false;
}
