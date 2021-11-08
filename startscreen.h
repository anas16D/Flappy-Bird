#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include <QDialog>

namespace Ui {
class startScreen;
}

class startScreen : public QDialog
{
    Q_OBJECT

public:
    explicit startScreen(QWidget *parent = nullptr);
    ~startScreen();

    QString getName() const;

private slots:
    void on_startButton_clicked();

private:
    Ui::startScreen *ui;
};

#endif // STARTSCREEN_H
