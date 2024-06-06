#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <QPainter>
#include <QRect>

class Obstacle {
public:
    Obstacle(int x, int y, int width, int height);
    void draw(QPainter *painter);
    QRect getRect() const;
    void setRect(const QRect &newRect);

private:
    QRect rect;
};

#endif // OBSTACLE_H
