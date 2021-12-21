#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include <QDialog>

namespace Ui {
class Startscreen;
}

class Startscreen : public QDialog
{
    Q_OBJECT

signals:
    void musicPlaying();

public:
    explicit Startscreen(QWidget *parent = nullptr);
    ~Startscreen();

    QString getName() const;



    void musicIconOn();
    void musicIconOff();

private slots:
    void on_startButton_clicked();

    void on_musicButton_clicked();

private:
    Ui::Startscreen *ui;
};

#endif // STARTSCREEN_H
