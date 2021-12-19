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

    bool collided();

    qreal m_x;
    int yPos;

public:
    explicit PillarItem(int durationOfPillar);
    ~PillarItem();
    int sc;
    bool birdPassed;

    qreal x() const;

    void freezePillars();

signals:
    void gameOver();

public slots:

    void setX(qreal x);
};

#endif // PillarItem_H
