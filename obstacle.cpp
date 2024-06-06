#include "obstacle.h"

Obstacle::Obstacle(int x, int y, int width, int height) : rect(x, y, width, height) {}

void Obstacle::draw(QPainter *painter) {
    painter->setBrush(Qt::red);
    painter->drawRect(rect);
}

QRect Obstacle::getRect() const {
    return rect;
}
void Obstacle::setRect(const QRect &newRect) {
    rect = newRect;
}
