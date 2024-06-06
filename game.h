#ifndef GAME_H
#define GAME_H
#include <QWidget>
#include <QTimer>
#include "player.h"
#include "ball.h"
#include "obstacle.h"
#include "powerup.h"


class Game : public QWidget
{
    Q_OBJECT

public:
    Game(int mode, QWidget *parent = nullptr);
    void startGame();


signals:
    void gameEnded(QString winner); // Señal para notificar el fin del juego

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private:
    void updateGame();
    void checkCollision();
    void spawnPowerUp();
    void gameOver();
    void resetGame();
    void addStaticObstacles();
    void addMovingObstacles();
    void applyPowerUp(PowerUp::PowerUpType type, Player* player);
    void moveObstacles();
    void generatePowerUp();
    void stopObstacles(); // Nueva función para detener obstáculos
    QTimer *obstacleTimer;


    static constexpr int MAX_SCORE = 5; // Puntaje máximo para ganar

    int mode; // 1 for single player, 2 for two players
    bool gameRunning;
    int score1;
    int score2;
    QString winner;
    Player *player1;
    Player *player2;
    Ball *ball;
    QTimer *timer;
    QTimer *powerUpEffectTimer;
    QTimer *powerUpTimer;
    QList<Obstacle*> obstacles;
    QList<PowerUp*> powerUps;
    bool isSpeedIncreased;
    bool isPaddleDoubled;
};

#endif // GAME_H

