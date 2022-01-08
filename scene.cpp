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



        connect(pillarItem, &PillarItem::gameOver, this,  [=](){
            pillarTimer->stop();
            //delete pillarTimer;

            backgroundTimer->stop();
            //delete backgroundTimer;

            freezeGame();
            setGameOn(false);

            emit gameOverScene();




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
    qDebug() <<"Score:" << score;

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

    if(!pillarTimer->isActive())
    {
        cleanPillars();
        //setUpPillarTimer();
        QThread::msleep(400);
        pillarTimer->start(800);

        backgroundTimer->start(20*1000);
        bird->setPos(-150,0);
    }

    bird->startFly();

    qDebug() << "game restarted";
}



