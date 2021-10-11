#ifndef BIRDITEM_H
#define BIRDITEM_H

#include <QObject>
#include <QGraphicsPixmapItem>

class BirdItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit BirdItem(QPixmap pixmap);
private:
    void updatePixmap();

    enum Position {Up, Middle, Down};
    Position wingPosition;
    bool wingDirection; // false: down, true: up

signals:

};

#endif // BIRDITEM_H
