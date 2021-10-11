#include "widget.h"
#include "ui_widget.h"
#include <QGraphicsPixmapItem>
#include "pillarItem.h"
#include "birditem.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{

    ui->setupUi(this);
    scene = new Scene(this);
    scene->setSceneRect(-250,-300,500,600);

    QGraphicsPixmapItem *pixItem = new QGraphicsPixmapItem(QPixmap(":/images/Sky2.jpg"));
    scene->addItem(pixItem);
    pixItem->setPos(QPointF(0,0) - QPointF(pixItem->boundingRect().width()/2, pixItem->boundingRect().height()/2));

    scene->addLine(-400,0,400,0,QPen(Qt::blue));
    scene->addLine(0,-400,0,400,QPen(Qt::blue));

    BirdItem *bird = new BirdItem(QPixmap(":/images/flappy_middle.png"));
    scene->addItem(bird);


//    PillarItem *pillar = new PillarItem();
//    scene->addItem(pillar);


    ui->graphicsView->setScene(scene);
    ui->graphicsView->scale(0.9,0.9);
}

Widget::~Widget()
{
    delete ui;
}

