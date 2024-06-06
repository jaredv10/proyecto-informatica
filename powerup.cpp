#include "powerup.h"

PowerUp::PowerUp(int x, int y, int width, int height, PowerUpType type)
    : rect(x, y, width, height), type(type) {}

void PowerUp::draw(QPainter *painter) {
    painter->setBrush(Qt::yellow);
    painter->drawRect(rect);
}

QRect PowerUp::getRect() const {
    return rect;
}

PowerUp::PowerUpType PowerUp::getType() const {
    return type;
}
void PowerUp::move() {
    // Ejemplo de movimiento simple: mover el power-up hacia abajo
    rect.moveTop(rect.top() + 1);
}

bool PowerUp::isOffScreen() const {
    // Comprueba si el power-up está fuera de los límites de la pantalla
    return rect.top() > 800;
}
