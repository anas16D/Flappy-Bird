#include "birditem.h"
#include <QTimer>

BirdItem::BirdItem(QPixmap pixmap): wingPosition(Up), wingDirection(false)
{
    setPixmap(pixmap);

    QTimer *wingsTimer = new QTimer(this);

    connect(wingsTimer, &QTimer::timeout, [=](){
        updatePixmap();
    });

    wingsTimer->start(100);

}

void BirdItem::updatePixmap()
{
    if(wingPosition == Middle)
    {
        if(wingDirection)       //UP
        {
            setPixmap(QPixmap(":/images/flappy_up.png"));
            wingPosition = Up;
            wingDirection = false;
        }
        else        // Down
        {
            setPixmap(QPixmap(":/images/flappy_down.png"));
            wingPosition = Down;
            wingDirection = true;
        }
    }
    else
    {
        setPixmap(QPixmap(":/images/flappy_middle.png"));
        wingPosition = Middle;;
    }


}
