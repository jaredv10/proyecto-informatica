#ifndef POWERUP_H
#define POWERUP_H
#include <QObject>
#include <QPainter>
#include <QRect>

class PowerUp {
public:
    enum PowerUpType {
        IncreaseSpeed,
        DoublePaddle
    };
    PowerUp(int x, int y, int width, int height, PowerUpType type);
    void draw(QPainter *painter);
    void move();
    PowerUpType getType() const;
    QRect getRect() const;
    bool isOffScreen() const;

private:
    QRect rect;
    int dy;
    PowerUpType type;
};

#endif // POWERUP_H
