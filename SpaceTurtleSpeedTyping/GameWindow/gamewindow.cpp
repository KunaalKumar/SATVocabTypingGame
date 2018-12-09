#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <QDebug>
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
    QString tutorial = "Press START to start the game. \n"
                       "Hit the enermy by spelling the word using keyboard. \n"
                       "There are three lives total. If user miss one enermy, they will lose one lives. \n";
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
