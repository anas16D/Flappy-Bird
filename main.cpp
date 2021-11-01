#include "widget.h"
#include <QIcon>

#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    Widget w;
//    w.ui->labelOutput->setText(QString("hello world"));
    w.show();
    w.setWindowTitle("Flappy Bird");
    w.setWindowIcon(QIcon(":/images/flappy.png"));



    return a.exec();
}
