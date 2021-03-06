#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <QKeyEvent>
#include <QMessageBox>
#include <iostream>
#include <QWidget>
#include <QVBoxLayout>
#include <QString>

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);

    ui->stackedWidget->insertWidget(1, &gameView);
    connect(&gameView, SIGNAL(homeClicked()), this, SLOT(moveHome()));
    connect(this, SIGNAL(signalGameStart()), &gameView, SLOT(startGame()));
    connect(this, SIGNAL(satGame()), &gameView, SLOT(satGame()));
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::keyPressEvent(QKeyEvent *event)
{

}

void GameWindow::on_gameStartButton_clicked()
{
    emit signalGameStart();
    ui->stackedWidget->setCurrentIndex(1);
}

void GameWindow::on_tutorialButton_clicked()
{
    QString tutorial = "Press START EASY GAME to start the game with the words advancing in length as you go. \n"
                        "\n"
                       "Press START SAT PREP to start the game with the words being the SAT Prep words advancing in words per round. \n"
                        "\n"
                       "Hit the enemy by spelling the word using keyboard. \n"
                        "\n"
                       "Once you target an enemy you must kill it. If you misspell the word you have to start the word over. \n"
                        "\n"
                       "If you get hit by an enemy you lose a life. You have three lives total. \n"
                        "\n"
                        "Good Luck.";
    QMessageBox::StandardButton box = QMessageBox::information(this, "Tutorial", tutorial, QMessageBox::Ok, QMessageBox::NoButton);
}

void GameWindow::moveHome()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void GameWindow::createGameScreen()
{

}

void GameWindow::on_pushButton_clicked()
{
    emit satGame();
    ui->stackedWidget->setCurrentIndex(1);
}
