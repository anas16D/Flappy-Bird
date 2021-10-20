#include "birditem.h"
#include <QTimer>

BirdItem::BirdItem(QPixmap pixmap): wingPosition(Up), wingDirection(false)
{
    // initial setting of bird's imamge
    setPixmap(pixmap);

    QTimer *wingsTimer = new QTimer(this);

    // connecting signal by wingTimer to he function updatePixmap
    // After each timeout, updatePixmap is called
    connect(wingsTimer, &QTimer::timeout, [=](){
        updatePixmap();
    });

    wingsTimer->start(120);

    groundPosition = scenePos().y() + 310;
    yAnimation = new QPropertyAnimation(this, "y", this);
    yAnimation->setStartValue(scenePos().y());
    yAnimation->setEndValue(groundPosition);
    yAnimation->setEasingCurve(QEasingCurve::InCirc);
    yAnimation->setDuration(4000);

    yAnimation->start();


    rotationAnimation = new QPropertyAnimation(this, "rotation", this);

    rotateTo(90, 2900, QEasingCurve::InQuad);



}

qreal BirdItem::y() const
{
    return m_y;
}

qreal BirdItem::rotation() const
{
    return m_rotation;
}

void BirdItem::setY(qreal y)
{
    moveBy(0, y-m_y);
    m_y = y;
}

void BirdItem::setRotation(qreal rotation)
{
    m_rotation = rotation;

    QPointF center = boundingRect().center();
    QTransform t;
    t.translate(center.x(), center.y());
    t.rotate(rotation);
    t.translate(-center.x(), -center.y());
    setTransform(t);
}

void BirdItem::rotateTo(const qreal &end, const int &duration, const QEasingCurve &curve)
{
    rotationAnimation->setStartValue(rotation());
    rotationAnimation->setEndValue(end);
    rotationAnimation->setEasingCurve(curve);
    rotationAnimation->setDuration(duration);

    rotationAnimation->start();
}

void BirdItem::updatePixmap()
{
    // if position of wings is at middle position, then we move it either up or down
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
    // if position of wings is NOT at middle position, then there is only option:
    //  move it in the middle
    else
    {
        setPixmap(QPixmap(":/images/flappy_middle.png"));
        wingPosition = Middle;;
    }


}
