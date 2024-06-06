#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "game.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void showMenu();

private slots:
    void showGameSelection();
    void startSinglePlayerGame();
    void startMultiPlayerGame();
    void showGameOverScreen();
    void quitGame();

private:
    Ui::MainWindow *ui;
    Game *game;
};

#endif // MAINWINDOW_H
