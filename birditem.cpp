#include "birditem.h"
#include <QTimer>
#include <QGraphicsScene>

BirdItem::BirdItem(QPixmap pixmap): wingPosition(Up), wingDirection(false)
{
    // initial setting of bird's imamge
    setPixmap(pixmap);

    wingsTimer = new QTimer(this);

    // connecting signal by wingTimer to he function updatePixmap
    // After each timeout, updatePixmap is called
    connect(wingsTimer, &QTimer::timeout, [=](){
        updatePixmap();
    });

    wingsTimer->start(120);

    groundPosition = scenePos().y() + 210;
    yAnimation = new QPropertyAnimation(this, "y", this);
//    yAnimation->setStartValue(scenePos().y());
//    yAnimation->setEndValue(groundPosition);
//    yAnimation->setEasingCurve(QEasingCurve::InCirc);
//    yAnimation->setDuration(4000);

//    yAnimation->start();

    //animateVericallyTo(groundPosition, 4000 ,QEasingCurve::InCirc);

    rotationAnimation = new QPropertyAnimation(this, "rotation", this);

    //rotateTo(90, 2900, QEasingCurve::InQuad);



}

qreal BirdItem::y() const
{
    return m_y;
}

qreal BirdItem::rotation() const
{
    return m_rotation;
}

void BirdItem::flapUp()
{
    yAnimation->stop();
    rotationAnimation->stop();

    qreal curPosY = y();
//    yAnimation->setStartValue(curPosY);
//    yAnimation->setEndValue(curPosY- scene()->sceneRect().height()/8);
//    yAnimation->setEasingCurve(QEasingCurve::OutQuad);
//    yAnimation->setDuration(280);
//    yAnimation->start();

    animateVericallyTo(curPosY- scene()->sceneRect().height()/10, 200,QEasingCurve::OutQuad);
    rotateTo(-20, 200, QEasingCurve::OutCubic);

    connect(yAnimation, &QPropertyAnimation::finished, [=](){

        if(y() < groundPosition)
        {
            rotationAnimation->stop();

            animateVericallyTo(groundPosition, 1000, QEasingCurve::InCubic);
            yAnimation->start();

            rotateTo(90, 1100, QEasingCurve::InCubic);
        }
    });

}

void BirdItem::startFly()
{
    animateVericallyTo(groundPosition, 1500 ,QEasingCurve::InCirc);
    rotateTo(90, 2900, QEasingCurve::InQuad);
    wingsTimer->start(120);

}

void BirdItem::freezeBird()
{
    yAnimation->stop();
    rotationAnimation->stop();
    wingsTimer->stop();

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

void BirdItem::animateVericallyTo(const qreal &end, const int &duration, const QEasingCurve &curve)
{
    yAnimation->setStartValue(y()); // current value as start value
    yAnimation->setEndValue(end);
    yAnimation->setEasingCurve(curve);
    yAnimation->setDuration(duration);

    yAnimation->start();
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
