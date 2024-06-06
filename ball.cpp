#include "ball.h"

Ball::Ball(int x, int y, int speed)
    : rect(x, y, 15, 15)
    , speedX(speed)
    , speedY(speed)
    , speedIncrement(1)
    , moveCounter(0)
{
}

void Ball::draw(QPainter *painter)
{
    painter->setBrush(Qt::red);
    painter->drawEllipse(rect);
}

void Ball::move()
{
    rect.moveLeft(rect.left() + speedX);
    rect.moveTop(rect.top() + speedY);

    if (rect.top() <= 0 || rect.bottom() >= 800) {
        reverseYDirection();
    }

    moveCounter++;


        if (moveCounter >= 500) {
            increaseSpeed();
            moveCounter = 0;
        }
}

QRect Ball::getRect() const
{
    return rect;
}

void Ball::reverseXDirection()
{
    speedX = -speedX;
}

void Ball::reverseYDirection()
{
    speedY = -speedY;
}

bool Ball::collidesWith(const QRect &rect)
{
    return this->rect.intersects(rect);
}

void Ball::increaseSpeed()
{
    if (speedX > 0) {
        speedX += speedIncrement;
    } else {
        speedX -= speedIncrement;
    }

    if (speedY > 0) {
        speedY += speedIncrement;
    } else {
        speedY -= speedIncrement;
    }
}

