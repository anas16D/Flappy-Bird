#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include <QDialog>

namespace Ui {
class switchScreen;
}

class switchScreen : public QDialog
{
    Q_OBJECT

public:
    explicit switchScreen(QWidget *parent = nullptr);
    ~switchScreen();

    QString getName() const;

private slots:
    void on_switchButton_clicked();

private:
    Ui::switchScreen *ui;
};

#endif // STARTSCREEN_H
