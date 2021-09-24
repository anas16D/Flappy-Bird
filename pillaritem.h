#ifndef PILLARITEM_H
#define PILLARITEM_H

#include <QGraphicsItemGroup>
#include <QGraphicsPixmapItem>

class pillarItem :public QObject, public QGraphicsItemGroup
{
    Q_OBJECT

private:
    QGraphicsPixmapItem *topPillar;
    QGraphicsPixmapItem *bottomPillar;

public:
    explicit pillarItem();

signals:

public slots:

};

#endif // PILLARITEM_H
