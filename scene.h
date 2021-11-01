#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include "pillaritem.h"
#include <QTimer>
#include <QElapsedTimer>
#include <QGraphicsPixmapItem>
#include "birditem.h"
#include <QPushButton>

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QGraphicsPixmapItem*, QObject *parent = nullptr);

    void addBird();

    void gameSwitch();




    bool getGameOn() const;
    void setGameOn(bool value);

signals:

public slots:
    void updateBackground(QGraphicsPixmapItem*);

private:
    void setUpPillarTimer(QGraphicsPixmapItem*);

    void freezeGame();

    void cleanPillars();

    bool day = true;
    //QGraphicsPixmapItem *pixItem;

    QTimer *pillarTimer;
    QTimer *backgroundTimer;
    BirdItem *bird ;

    bool gameOn;



    // QGraphicsScene interface
protected:
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // SCENE_H
