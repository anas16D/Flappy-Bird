#include "startscreen.h"
#include "ui_switchscreen.h"
#include <QDebug>


switchScreen::switchScreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::switchScreen)
{

    ui->setupUi(this);

    ui->switchButton->setEnabled(false);

    connect(ui->playerName, &QLineEdit::textChanged, [=](){

        if(!(ui->playerName->text().isEmpty()))
        {
            ui->switchButton->setEnabled(true);
            qDebug() << getName();
        }
        else
        {
            ui->switchButton->setEnabled(false);
        }
    });


}



switchScreen::~switchScreen()
{
    delete ui;
}

QString switchScreen::getName() const
{

    return ui->playerName->text();
}

void switchScreen::on_switchButton_clicked()
{

    this->done(0);
}
