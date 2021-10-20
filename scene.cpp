#include "scene.h"
#include <QRandomGenerator>
#include <QGraphicsPixmapItem>
#include <QDebug>

Scene::Scene(QGraphicsPixmapItem *pixItem, QObject *parent) : QGraphicsScene(parent)
{
    //QGraphicsPixmapItem *pixItem = new QGraphicsPixmapItem(QPixmap(":/images/nightSky.jpg"));

    setUpPillarTimer(pixItem);

    //this->update(pixItem);





}

void Scene::setUpPillarTimer(QGraphicsPixmapItem* pixItem)
{
    QTimer *backgroundTimer = new QTimer(this);

    int durationOfPillar = 0;


    QElapsedTimer *gameDuration = new QElapsedTimer();
    gameDuration->start();

    connect(backgroundTimer, &QTimer::timeout, this, [=](){
        updateBackground(pixItem);
        qDebug() << "Remaining Time : " << backgroundTimer->remainingTime();

    });
    backgroundTimer->start(10000);

    pillarTimer = new QTimer(this);
    connect(pillarTimer, &QTimer::timeout,this, [=]()mutable{
        PillarItem *pillarItem = new PillarItem(durationOfPillar);
        addItem(pillarItem);

        if(gameDuration->elapsed() < 130*1000)
        {
            durationOfPillar += 4;
        }


        if(durationOfPillar > 404 && gameDuration->elapsed() < 100*000)
        {
            pillarTimer->setInterval(900-durationOfPillar);
            durationOfPillar -= 100;
        }

        if(gameDuration->elapsed() > 100*1000 && gameDuration->elapsed() < 101*1000)
        {
            pillarTimer->setInterval(300);
            durationOfPillar -= 150;
        }


        qDebug() << "Duration : " << durationOfPillar;



    });

    pillarTimer->start(800);
    qDebug() << "Hello";

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

