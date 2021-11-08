#include "gameoverscreen.h"
#include "ui_gameoverscreen.h"
#include <QDebug>
#include "widget.h"

GameOverScreen::GameOverScreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameOverScreen)
{
    ui->setupUi(this);

    //ui->label->setText(widget);
}

GameOverScreen::~GameOverScreen()
{
    delete ui;
}




void GameOverScreen::on_RestartButton_clicked()
{
    this->done(0);
}

void GameOverScreen::on_exitButton_clicked()
{
    qDebug() << "exit button clicked";
    emit endGame();
}
