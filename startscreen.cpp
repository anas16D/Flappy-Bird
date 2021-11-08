#include "startscreen.h"
#include "ui_startscreen.h"
#include <QDebug>


startScreen::startScreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::startScreen)
{

    ui->setupUi(this);

    ui->startButton->setEnabled(false);

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



startScreen::~startScreen()
{
    delete ui;
}

QString startScreen::getName() const
{

    return ui->playerName->text();
}

void startScreen::on_startButton_clicked()
{

    this->done(0);
}
