#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <QDebug>
#include <QKeyEvent>
#include "../GameLib/status.h"
#include <QMessageBox>
#include <iostream>
#include <QWidget>
#include "../GameLib/gamelib.h"
#include "Box2D/Box2D.h"

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::keyPressEvent(QKeyEvent *event)
{
    // Only inside of the game screen we take keyboard inputs
    if (ui->stackedWidget->currentIndex() == 1)
        qDebug() << " Key Pressed: " << (char)event->key();
}

void GameWindow::on_gameStartButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void GameWindow::on_endGameButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void GameWindow::on_tutorialButton_clicked()
{
    qDebug() << "tutorial button pressed";
    QMessageBox::StandardButton box = QMessageBox::information(this, "Tutorial", "This is toturial",                                                              QMessageBox::Ok, QMessageBox::NoButton);
}

void GameWindow::on_optionButton_clicked()
{
    qDebug() << "option button pressed";
    QMessageBox::StandardButton box = QMessageBox::information(this, "Option", "Back to Title",                                                              QMessageBox::Ok, QMessageBox::NoButton);
}
