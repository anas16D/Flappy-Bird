#ifndef PillarItem_H
#define PillarItem_H

#include <QGraphicsItemGroup>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>

class PillarItem :public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX)

private:
    QGraphicsPixmapItem *topPillar;
    QGraphicsPixmapItem *bottomPillar;
    QPropertyAnimation *xAnimation;

    qreal m_x;
    int yPos;

public:
    explicit PillarItem();
    ~PillarItem();

    qreal x() const;

signals:

public slots:

    void setX(qreal x);
};

#endif // PillarItem_H
