#ifndef BIRDITEM_H
#define BIRDITEM_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>

class BirdItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(qreal rotation READ rotation WRITE setRotation)
    Q_PROPERTY(qreal y READ y WRITE setY)


public:
    explicit BirdItem(QPixmap pixmap);

    qreal y() const;
    qreal rotation() const;

public slots:

    void setY(qreal y);
    void setRotation(qreal rotation);
    void rotateTo(const qreal &end, const int &duration, const QEasingCurve &curve);

private:
    void updatePixmap();

    enum Position {Up, Middle, Down};
    Position wingPosition;
    bool wingDirection; // false: down, true: up

    qreal m_y;
    qreal m_rotation;

    qreal groundPosition;

    QPropertyAnimation *yAnimation;
    QPropertyAnimation *rotationAnimation;

signals:

};

#endif // BIRDITEM_H
