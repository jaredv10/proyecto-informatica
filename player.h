#ifndef PLAYER_H
#define PLAYER_H

#include <QRect>
#include <QPainter>

class Player {
public:
    enum Direction { None, Up, Down };
    Player(int x, int y, bool isAI = false); // Agregar parámetro isAI para distinguir entre jugador y IA

    void draw(QPainter *painter);
    void move();
    void moveAI(const QRect &ballRect); // Agregar función para mover la IA
    QRect getRect() const;
    void setDirection(Direction dir);
    void stop();
    void setUpPressed(bool pressed);
    void setDownPressed(bool pressed);
    void setSpeed(int speed);
    void doubleSize();
    void resetSize();
    int getSpeed() const;

private:
    QRect rect;
    Direction direction;
    int speed;
    bool isAI;
    bool upPressed;
    bool downPressed;
    int originalHeight;
};

#endif // PLAYER_H

