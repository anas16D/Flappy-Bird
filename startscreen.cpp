             #include "startscreen.h"
#include "ui_startscreen.h"
#include <QDebug>


Startscreen::Startscreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Startscreen)
{

    ui->setupUi(this);

    ui->startButton->setEnabled(false);

    ui->musicButton->setIcon(QIcon(":/images/musicON.png"));
    ui->musicButton->setIconSize(QSize(20,20));

//    connect(ui->musicButton, &QPushButton::clicked, [=](){

//        if(mu)

//    });

    connect(ui->playerName, &QLineEdit::textChanged, [=](){

        if(!(ui->playerName->text().isEmpty()))
        {
            ui->startButton->setEnabled(true);
            qDebug() << getName();
        }
        else
        {
            ui->startButton->setEnabled(false);
        }
    });


}



Startscreen::~Startscreen()
{
    qDebug() << "detroyed start screen";
    delete ui;
}

QString Startscreen::getName() const
{

    return ui->playerName->text();
}

void Startscreen::musicIconOn()
{
    ui->musicButton->setIcon(QIcon(":/images/musicON.png"));
}

void Startscreen::musicIconOff()
{
    ui->musicButton->setIcon(QIcon(":/images/musicOFF.png"));

}

void Startscreen::on_startButton_clicked()
{
    //this->close();

    this->done(0);
}

void Startscreen::on_musicButton_clicked()
{
    qDebug() << "muisic button clicked";
    emit musicPlaying();
}
