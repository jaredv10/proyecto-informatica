#include "player.h"
#include <QDebug>

Player::Player(int x, int y, bool isAI)
    : rect(x, y, 10, 100) // Ajustar el tamaño según sea necesario
    , direction(None)
    , isAI(isAI)
    , speed(10)
{
}

void Player::draw(QPainter *painter)
{
    painter->setBrush(Qt::blue); // Cambiar color si es necesario
    painter->drawRect(rect);
}

void Player::move()
{
    if (direction == Up) {
        rect.moveTop(rect.top() - speed);
    } else if (direction == Down) {
        rect.moveTop(rect.top() + speed);
    }

    if (rect.top() < 0) {
        rect.moveTop(0);
    } else if (rect.bottom() > 800) { // Suponiendo que el campo de juego tiene una altura de 800
        rect.moveBottom(800);
    }
}


void Player::moveAI(const QRect &ballRect)
{
    if (ballRect.center().y() < rect.center().y()) {
        rect.moveTop(rect.top() - 5);
    } else if (ballRect.center().y() > rect.center().y()) {
        rect.moveTop(rect.top() + 5);
    }

    // Limitar el movimiento dentro del área del juego
    if (rect.top() < 0) {
        rect.moveTop(0);
    } else if (rect.bottom() > 800) {
        rect.moveBottom(800);
    }
}

QRect Player::getRect() const
{
    return rect;
}

void Player::setDirection(Direction dir)
{
    direction = dir;
}

int Player::getSpeed() const {
    return speed;
}

void Player::setUpPressed(bool pressed) {
    upPressed = pressed;
}

void Player::setDownPressed(bool pressed) {
    downPressed = pressed;
}

void Player::setSpeed(int speed) {
    this->speed = speed;
}

void Player::doubleSize() {
    originalHeight = rect.height();
    rect.setHeight(rect.height() * 2);
}

void Player::resetSize() {
    rect.setHeight(originalHeight);
}

