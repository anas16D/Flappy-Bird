#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "scene.h"
#include "startscreen.h"
#include <QMediaPlaylist>
#include <QMediaPlayer>


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void musicIconOn();
    void musicIconOff();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_released();

    void on_musicButton_clicked();

    void on_musicButton_released();

private:
    Ui::Widget *ui;
    Scene * scene;

    QMediaPlaylist *musicList;
    QMediaPlayer *music;

    bool musicPlaying;


};
#endif // WIDGET_H
