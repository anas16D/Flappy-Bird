#include "scene.h"
#include <QRandomGenerator>
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <QFont>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QThread>


Scene::Scene(QGraphicsPixmapItem *pixItem, QObject *parent) : QGraphicsScene(parent),
    gameOn(false), score(0)
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
    if(this->getGameOn())
    {
        this->freezeGame();
        setGameOn(false);
        pillarTimer->stop();
        return;
    }



    setGameOn(true);

    if(!pillarTimer->isActive())
    {
        //cleanPillars();
        pillarTimer->start(800);
        backgroundTimer->start(20*1000);
        //bird->setPos(-150,0);
    }

    QList<QGraphicsItem*> sceneItems = items();

    foreach(QGraphicsItem *item, sceneItems)
    {
        PillarItem *pillar = dynamic_cast<PillarItem*>(item);

        if(pillar)
        {
            pillar->unfreezePillars();
        }
    }

    bird->startFly();
}


void Scene::setUpPillarTimer(QGraphicsPixmapItem* pixItem)
{
    backgroundTimer = new QTimer(this);

    int durationOfPillar = 0;


    gameDuration = new QElapsedTimer();
    gameDuration->start();

    connect(backgroundTimer, &QTimer::timeout, this, [=](){
        updateBackground(pixItem);
        qDebug() << "Remaining Time : " << backgroundTimer->remainingTime();

    });
    backgroundTimer->start(20*1000);

    pillarTimer = new QTimer(this);


    connect(pillarTimer, &QTimer::timeout,this, [=]()mutable{
        PillarItem *pillarItem = new PillarItem(durationOfPillar);

        qDebug() << "Duration Of Pillar = " << durationOfPillar;
        qDebug() << "game Durtion = " << gameDuration->elapsed();




        connect(pillarItem, &PillarItem::gameOver, this,  [=](){


            pillarTimer->stop();


            backgroundTimer->stop();

            bird->setScale(1);


            freezeGame();
            setGameOn(false);

            //gameDuration->restart();

            emit gameOverScene();




        });

        addItem(pillarItem);


        if(gameDuration->elapsed() < 150*1000)
        {
            durationOfPillar += 2;
        }


        if(durationOfPillar > 250)
        {

            durationOfPillar -= 50;
        }

        if(gameDuration->elapsed() > 10*1000 && gameDuration->elapsed() < 10.5*1000)
        {
            pillarTimer->setInterval(540);
            bird->setScale(.8);

        }

        if(gameDuration->elapsed() > 15*1000 && gameDuration->elapsed() < 15.5*1000)
        {
             pillarTimer->setInterval(340);
             bird->setScale(.8);

        }




    });




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
            //delete pillar;
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

void Scene::incrementScore()
{
    score++;
    //qDebug() <<"Score:" << score;

    emit updateScore();
}

QString Scene::getScore() const
{
    int temp = score;
    QString ans  = "";
    while(temp)
    {
        char sc = static_cast<char>((temp%10) + '0');
        temp = temp/10;
        ans += sc;
    }
    std::reverse(ans.begin(), ans.end());

    return "Score: " + ans;
}

void Scene::restartGame()
{
    score = 0;

    qDebug() << "Restart game";

    setGameOn(true);

    gameDuration->restart();



    if(!pillarTimer->isActive())
    {
        cleanPillars();
        //setUpPillarTimer();
        //QThread::msleep(400);
        pillarTimer->start(800);

        backgroundTimer->start(20*1000);
        bird->setPos(-150,0);
    }

    bird->startFly();

    qDebug() << "game restarted";
}



