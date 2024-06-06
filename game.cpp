#include "game.h"
#include <QPainter>
#include <QKeyEvent>
#include <QRandomGenerator>
#include <QDebug>
#include <QTimerEvent>
#include "powerup.h"

Game::Game(int mode, QWidget *parent)
    : QWidget(parent)
    , mode(mode)
    , gameRunning(false)
    , score1(0)
    , score2(0)
    , player1(new Player(50, 400))
    , player2(new Player(1150, 400, mode == 1))
    , ball(new Ball(600, 400, 5))
    , timer(new QTimer(this))
    , obstacleTimer(new QTimer(this))
{
    setFixedSize(1200, 800);
    setFocusPolicy(Qt::StrongFocus);
    connect(timer, &QTimer::timeout, this, &Game::updateGame);
    connect(obstacleTimer, &QTimer::timeout, this, &Game::moveObstacles);
}

void Game::addStaticObstacles()
{

    obstacles.append(new Obstacle(300, 200, 20, 100));
    obstacles.append(new Obstacle(700, 500, 20, 100));
    obstacles.append(new Obstacle(500, 300, 20, 100));
}

void Game::addMovingObstacles()
{

    obstacles.append(new Obstacle(400, 100, 20, 100));
    obstacles.append(new Obstacle(800, 400, 20, 100));
}

void Game::moveObstacles()
{
    for (auto obstacle : obstacles) {
        QRect rect = obstacle->getRect();
        rect.moveTop(rect.top() + 5);
        if (rect.bottom() > height()) {
            rect.moveTop(0);
        }
        obstacle->setRect(rect);
    }
    update();
}

void Game::startGame()
{
    gameRunning = true;
    score1 = 0;
    score2 = 0;
    winner .clear();
    addStaticObstacles();
    addMovingObstacles();
    timer->start(16);
    obstacleTimer->start(50);
}


void Game::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    if (gameRunning) {
        player1->draw(&painter);
        player2->draw(&painter);
        ball->draw(&painter);

        for (auto obstacle : obstacles) {
            obstacle->draw(&painter);
        }

        for (auto powerUp : powerUps) {
            powerUp->draw(&painter);
        }


        painter.setPen(QColor("#ff1f16"));
        QFont scoreFont("Comic Sans MS", 24, QFont::Bold);
        painter.setFont(scoreFont);
        painter.drawText(50, 50, QString("Player 1: %1").arg(score1));
        painter.drawText(width() - 200, 50, QString("Player 2: %1").arg(score2));
    } else {
        QFont font("Kristen ITC", 40, QFont::Bold);
                painter.setFont(font);
                painter.setPen(QColor("#FFEB3B"));


                QRectF textRect = rect().adjusted(20, 20, -20, -20);


                Qt::Alignment alignment = Qt::AlignCenter;


                QLinearGradient gradient(textRect.topLeft(), textRect.bottomRight());
                gradient.setColorAt(0, QColor(125, 31, 162));
                gradient.setColorAt(1, QColor(221, 44, 0));
                painter.setBrush(gradient);
                painter.drawRoundedRect(textRect, 10, 10);


                painter.drawText(textRect, alignment | Qt::TextWordWrap, "GAME OVER \n");
                painter.drawText(rect(), Qt::AlignCenter, QString("\n Winner: %1").arg(winner));
    }
}

void Game::keyPressEvent(QKeyEvent *event)
{
    if (!gameRunning) {
        if (event->key() == Qt::Key_Space) {
            startGame();
        }
        return;
    }

    switch (event->key()) {
        case Qt::Key_W:
            player1->setDirection(Player::Up);
            break;
        case Qt::Key_S:
            player1->setDirection(Player::Down);
            break;
        case Qt::Key_Up:
            if (mode == 2) player2->setDirection(Player::Up);
            break;
        case Qt::Key_Down:
            if (mode == 2) player2->setDirection(Player::Down);
            break;
        default:
            QWidget::keyPressEvent(event);
    }
}

void Game::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_W:
        case Qt::Key_S:
            player1->setDirection(Player::None);
            break;
        case Qt::Key_Up:
        case Qt::Key_Down:
            if (mode == 2) player2->setDirection(Player::None);
            break;
        default:
            QWidget::keyReleaseEvent(event);
    }
}

void Game::updateGame() {
    player1->move();
    if (mode == 1) {
        player2->moveAI(ball->getRect());
    } else {
        player2->move();
    }
    ball->move();
    checkCollision();
    update();

    if (QRandomGenerator::global()->bounded(100) < 1) {
        generatePowerUp();
    }

    for (auto it = powerUps.begin(); it != powerUps.end();) {
        (*it)->move();
        if ((*it)->isOffScreen()) {
            delete *it;
            it = powerUps.erase(it);
        } else {
            ++it;
        }
    }

    static int timeCounter = 0;
    if (++timeCounter % 1000 == 0) {
        ball->increaseSpeed();
    }
}

void Game::checkCollision()
{
    if (ball->collidesWith(player1->getRect()) || ball->collidesWith(player2->getRect())) {
        ball->reverseXDirection();

    }

    for (auto obstacle : obstacles) {
        if (ball->collidesWith(obstacle->getRect())) {
            ball->reverseXDirection();
        }
    }

    for (auto it = powerUps.begin(); it != powerUps.end();) {
        if (ball->collidesWith((*it)->getRect())) {
            delete *it;
            it = powerUps.erase(it);
        } else {
            ++it;
        }
    }

    if (ball->getRect().left() <= 0) {
        score2++;
        winner = "Player 2";
        if (score2 >= MAX_SCORE) {
            gameOver();
        } else {
            resetGame();
        }
    } else if (ball->getRect().right() >= width()) {
        score1++;
        winner = "Player 1";
        if (score1 >= MAX_SCORE) {
            gameOver();
        } else {
            resetGame();
        }
    }
}

void Game::applyPowerUp(PowerUp::PowerUpType type, Player *player) {
    switch (type) {
        case PowerUp::IncreaseSpeed:
            player->setSpeed(player->getSpeed() + 5);
            break;
        case PowerUp::DoublePaddle:
            player->doubleSize();
            break;
    }


    QTimer::singleShot(10000, [player, type]() {
        if (type == PowerUp::IncreaseSpeed) {
            player->setSpeed(player->getSpeed() - 5);
        } else if (type == PowerUp::DoublePaddle) {
            player->resetSize();
        }
    });
}

void Game::generatePowerUp() {
    int x = QRandomGenerator::global()->bounded(100, 1100);
    int y = QRandomGenerator::global()->bounded(100, 700);
    PowerUp::PowerUpType type = static_cast<PowerUp::PowerUpType>(QRandomGenerator::global()->bounded(2));
    powerUps.append(new PowerUp(x, y, 20, 20, type));
    update();
}

void Game::resetGame()
{

    delete ball;
    ball = new Ball(600, 400, 5);
    player1->setDirection(Player::None);
    player2->setDirection(Player::None);
}

void Game::gameOver()
{
    gameRunning = false;
    timer->stop();
    emit gameEnded(winner);
}
