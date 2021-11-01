#include "widget.h"
#include "ui_widget.h"
#include <QGraphicsPixmapItem>
#include "pillaritem.h"
#include "birditem.h"
#include <QDebug>
#include <QMediaPlaylist>
#include <QMediaPlayer>




Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{

    QMediaPlaylist *musicList = new QMediaPlaylist();
    musicList->addMedia(QUrl("qrc:/Audio/TRG_Banks_-_08_-_A_Christmas_adventure_Part_1-1 (1) (1).mp3"));
    musicList->setPlaybackMode(QMediaPlaylist::Loop);

    QMediaPlayer *music = new QMediaPlayer();
    music->setPlaylist(musicList);
    music->play();


    switchScreen *screen  = new switchScreen;

    screen->setWindowIcon(QIcon(":/images/flappy.png"));
    screen->setWindowTitle("Flappy Bird");
    screen->setStyleSheet("QDialog{background-image: url(:/images/nightSky.jpg);}");
    screen->exec();




    ui->setupUi(this);

    ui->label->setText(screen->getName());
    QGraphicsPixmapItem *pixItem = new QGraphicsPixmapItem(QPixmap(":/images/Sky2.jpg"));


    scene = new Scene(pixItem, this);
    scene->setSceneRect(-250,-300,500,600);

    scene->addItem(pixItem);
    pixItem->setPos(QPointF(0,0) - QPointF(pixItem->boundingRect().width()/2, pixItem->boundingRect().height()/2));

    scene->addLine(-400,0,400,0,QPen(Qt::blue));
    scene->addLine(0,-400,0,400,QPen(Qt::blue));

//    BirdItem *bird = new BirdItem(QPixmap(":/images/flappy_middle.png"));
//    scene->addItem(bird);


//    PillarItem *pillar = new PillarItem();
//    scene->addItem(pillar);


    scene->addBird();


    ui->graphicsView->setScene(scene);
    ui->graphicsView->scale(0.7,0.88);



}


Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    if(scene->getGameOn())
    {
//        switchScreen *screen  = new switchScreen;
//        screen->setWindowIcon(QIcon(":/images/flappy.png"));
//        screen->setWindowTitle("Flappy Bird");
//        screen->setStyleSheet("QDialog{background-image: url(:/images/nightSky.jpg);}");
//        screen->exec();
    }

    qDebug() << "push button clicked";
    scene->gameSwitch();

}

void Widget::on_pushButton_released()
{
   ui->pushButton->clearFocus();

   ui->graphicsView->setFocus();






}
