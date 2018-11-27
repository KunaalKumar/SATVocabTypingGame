#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <QDebug>
#include <QKeyEvent>
#include "../GameLib/status.h"
#include <QMessageBox>
#include <iostream>
#include <QWidget>

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
    std::cout<<"tutorial clicked!"<<std::endl;

    QMessageBox::StandardButton box = QMessageBox::information(this, "Tutorial", "This is toturial",
                                                               QMessageBox::Ok, QMessageBox::NoButton);
   if(box == QMessageBox::Ok)
       QApplication::quit();
}
