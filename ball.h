#ifndef BALL_H
#define BALL_H

#include <QRect>
#include <QPainter>

class Ball {
public:
    Ball(int x, int y, int speed);

    void draw(QPainter *painter);
    void move();
    QRect getRect() const;
    void reverseXDirection();
    void reverseYDirection();
    bool collidesWith(const QRect &rect);
    void increaseSpeed();

private:
    QRect rect;
    int speedX;
    int speedY;
    int speedIncrement;
    int moveCounter;
};

#endif // BALL_H
