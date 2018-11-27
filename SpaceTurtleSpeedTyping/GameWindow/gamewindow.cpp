#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <QDebug>
#include <QKeyEvent>

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    importWords();
}

void GameWindow::importWords(){
    QFile file("..//src/dictionary/words");
    //if it fails to read the file
    if(!file.open(QIODevice::ReadOnly)){

    }
    //else take all the words and put it into the vector listOfWords
    QTextStream output(&file);
    while(!output.atEnd()){
        QString line = output.readLine();
        listOfWords.append(line);
    }
    qDebug()<< "Number of words read = " << listOfWords.length();
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
