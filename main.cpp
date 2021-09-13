#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    Widget w;
//    w.ui->labelOutput->setText(QString("hello world"));
    w.show();
    return a.exec();
}
