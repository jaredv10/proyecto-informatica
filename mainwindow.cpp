#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , game(nullptr)
{
    ui->setupUi(this);
    connect(ui->returnToMenuButton, &QPushButton::clicked, this, &MainWindow::showMenu);

}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showMenu()
{
    ui->stackedWidget->setCurrentIndex(0); // Asumiendo que la pantalla de menú principal es la primera en stackedWidget

    connect(ui->playButton, &QPushButton::clicked, this, &MainWindow::showGameSelection);
    connect(ui->aboutButton, &QPushButton::clicked, [this] {
        QMessageBox messageBox;
            messageBox.setWindowTitle("Acerca de");
            QString messageText =
                "<h2><u>Pong</u></h2>"
                "<p>Pong es un juego de deportes en el que dos jugadores controlan paletas en los extremos opuestos de la pantalla, compitiendo entre sí para golpear una pelota y evitar que llegue a su lado de la pantalla. El objetivo es anotar puntos haciendo que la pelota pase al lado del oponente sin ser devuelta.</p>"
                "<h3>Modos de juego:</h3>"
                "<ul>"
                "<li><b>Jugador vs. IA (Inteligencia Artificial):</b> En este modo, el jugador compite contra la computadora. Controlarás una paleta utilizando las teclas W (para mover hacia arriba) y S (para mover hacia abajo) para golpear la pelota y evitar que llegue a tu lado de la pantalla.</li>"
                "<li><b>Jugador vs. Jugador:</b> En este modo, dos jugadores compiten entre sí. El jugador uno utiliza las teclas W y S para controlar su paleta, mientras que el jugador dos utiliza las flechas hacia arriba y hacia abajo del teclado.</li>"
                "</ul>"
                "<h3>Obstáculos:</h3>"
                "<p>En Pong, los obstáculos añaden un desafío adicional al juego. Estos aparecen como barras en la pantalla con las que la pelota puede chocar y rebotar. A medida que la partida avanza, la velocidad de la pelota aumenta, lo que hace más difícil golpearla con precisión y evitar que pase al lado del oponente. El control preciso de las paletas se vuelve crucial para superar estos obstáculos y ganar la partida.</p>";

            messageBox.setText(messageText);
            messageBox.exec();
        });
    connect(ui->exitButton, &QPushButton::clicked, this, &MainWindow::quitGame);
}

void MainWindow::showGameSelection()
{
    ui->stackedWidget->setCurrentIndex(1); // Asumiendo que la pantalla de selección de modo de juego es la segunda en stackedWidget

    connect(ui->singlePlayerButton, &QPushButton::clicked, this, &MainWindow::startSinglePlayerGame);
    connect(ui->multiPlayerButton, &QPushButton::clicked, this, &MainWindow::startMultiPlayerGame);
    connect(ui->backButton, &QPushButton::clicked, this, &MainWindow::showMenu);
}

void MainWindow::startSinglePlayerGame()
{
    if (game != nullptr) {
        delete game;
    }

    game = new Game(1, this); // Asumiendo que 1 significa modo un jugador
    setCentralWidget(game);
    game->startGame();
    game->setFocus(); // Asegurar que el widget de juego recibe el foco del teclado
}

void MainWindow::startMultiPlayerGame()
{
    if (game != nullptr) {
        delete game;
    }

    game = new Game(2, this); // Asumiendo que 2 significa modo dos jugadores
    setCentralWidget(game);
    game->startGame();

}

void MainWindow::showGameOverScreen()
{
    ui->stackedWidget->setCurrentIndex(2);
    connect(ui->returnToMenuButton, &QPushButton::clicked, this, &MainWindow::showMenu);
}

void MainWindow::quitGame()
{
    QApplication::quit();
}

