#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include "pillaritem.h"
#include <QTimer>
#include <QElapsedTimer>
#include <QGraphicsPixmapItem>

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QGraphicsPixmapItem*, QObject *parent = nullptr);

signals:

public slots:
    void updateBackground(QGraphicsPixmapItem*);

private:
    void setUpPillarTimer(QGraphicsPixmapItem*);

    bool day = true;
    //QGraphicsPixmapItem *pixItem;

    QTimer *pillarTimer;

};

#endif // SCENE_H
