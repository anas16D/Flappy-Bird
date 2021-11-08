#ifndef GAMEOVERSCREEN_H
#define GAMEOVERSCREEN_H

#include <QDialog>

namespace Ui {
class GameOverScreen;
}

class GameOverScreen : public QDialog
{
    Q_OBJECT

public:
    explicit GameOverScreen(QWidget *parent = nullptr);
    ~GameOverScreen();

signals:
    void endGame();

private slots:




    void on_RestartButton_clicked();

    void on_exitButton_clicked();

private:
    Ui::GameOverScreen *ui;
};

#endif // GAMEOVERSCREEN_H
