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
    explicit Scene();

    void addBird();

    void gameSwitch();

    void incrementScore();

    QString getScore() const;

    void restartGame();




    bool getGameOn() const;
    void setGameOn(bool value);

signals:

    void gameOverScene();

    void updateScore();



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

    int score;



    // QGraphicsScene interface
protected:
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // SCENE_H
