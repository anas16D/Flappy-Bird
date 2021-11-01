#include "scene.h"
#include <QRandomGenerator>
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <QFont>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>

Scene::Scene(QGraphicsPixmapItem *pixItem, QObject *parent) : QGraphicsScene(parent),
    gameOn(false)
{

    setUpPillarTimer(pixItem);

}

void Scene::addBird()
{
    bird = new BirdItem(QPixmap(":/images/flappy_middle.png"));
    bird->setPos(-150,0);
    addItem(bird);
}

void Scene::gameSwitch()
{

    bird->startFly();

    setGameOn(true);

    if(!pillarTimer->isActive())
    {
        cleanPillars();
        pillarTimer->start(800);
        backgroundTimer->start();
        bird->setPos(-150,0);
    }
}


void Scene::setUpPillarTimer(QGraphicsPixmapItem* pixItem)
{
    backgroundTimer = new QTimer(this);

    int durationOfPillar = 0;


    QElapsedTimer *gameDuration = new QElapsedTimer();
    gameDuration->start();

    connect(backgroundTimer, &QTimer::timeout, this, [=](){
        updateBackground(pixItem);
        qDebug() << "Remaining Time : " << backgroundTimer->remainingTime();

    });
    backgroundTimer->start(20*1000);

    pillarTimer = new QTimer(this);


    connect(pillarTimer, &QTimer::timeout,this, [=]()mutable{
        PillarItem *pillarItem = new PillarItem(durationOfPillar);



        connect(pillarItem, &PillarItem::gameOver, [=](){
            pillarTimer->stop();
            backgroundTimer->stop();
            freezeGame();
            setGameOn(false);


        });

        addItem(pillarItem);


        if(gameDuration->elapsed() < 150*1000)
        {
            durationOfPillar += 2;
        }


        if(durationOfPillar > 200 && gameDuration->elapsed() < 100*1000)
        {
            pillarTimer->setInterval(800-durationOfPillar);
            durationOfPillar -= 50;
        }

        if(gameDuration->elapsed() > 100*1000 && gameDuration->elapsed() < 100.5*1000)
        {
            pillarTimer->setInterval(340);
            durationOfPillar -= 100;
        }


        qDebug() << "Duration : " << durationOfPillar;


    });

    //pillarTimer->start(800);

//    connect(pauseButton, &QPushButton::released, this, [=](){
//       disconnect(pillarTimer, &QTimer::timeout, this, 0);
//       //disconnect(backgroundTimer);
//        pillarTimer->stop();
//        backgroundTimer->stop();
//       qDebug() << "Hello";
//    });





}

void Scene::freezeGame()
{
    bird->freezeBird();


    QList<QGraphicsItem*> sceneItems = items();


    foreach(QGraphicsItem *item, sceneItems)
    {
        PillarItem *pillar = dynamic_cast<PillarItem*>(item);

        if(pillar)
        {
            pillar->freezePillars();
        }
    }

}

void Scene::cleanPillars()
{
    QList<QGraphicsItem*> sceneItems = items();


    foreach(QGraphicsItem *item, sceneItems)
    {
        PillarItem *pillar = dynamic_cast<PillarItem*>(item);

        if(pillar)
        {
            this->removeItem(pillar);
            delete pillar;
        }
    }
}

bool Scene::getGameOn() const
{
    return gameOn;
}

void Scene::setGameOn(bool value)
{
    gameOn = value;
}

void Scene::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Space && gameOn)
    {
        bird->flapUp();
    }
    QGraphicsScene::keyPressEvent(event);
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && gameOn)
    {
        bird->flapUp();
    }
    QGraphicsScene::mousePressEvent(event);
}

void Scene::updateBackground(QGraphicsPixmapItem* pixItem)
{
    qDebug() << "Update Background functon called";
    if(day)
    {
        day = false;
        pixItem->setPixmap(QPixmap(":/images/nightSky.jpg"));
    }
    else
    {
        day = true;
        pixItem->setPixmap(QPixmap(":/images/Sky2.jpg"));
    }
}



