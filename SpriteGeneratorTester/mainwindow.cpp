#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsPixmapItem>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    sg("/home/nathan/source/A8-an-educational-app-f18-Purple-Picnic-Turtles-2.0/SpriteGenerator/SpriteStructures/")
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_smallSpriteButton_clicked()
{
    try
    {
        QImage newSprite = sg.generatreNewSprite(SpriteSize::small);
        QGraphicsScene* scene = new QGraphicsScene();
        QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(newSprite).scaled(600,600));
        scene->addItem(item);

        ui->graphicsView->setScene(scene);
    }
    catch (char const* msg)
    {
        qInfo() << msg;
    }
}

void MainWindow::on_mediumSprietButton_clicked()
{
    try
    {
    QImage newSprite = sg.generatreNewSprite(SpriteSize::medium);
    QGraphicsScene* scene = new QGraphicsScene();
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(newSprite).scaled(600,600));
    scene->addItem(item);

    ui->graphicsView->setScene(scene);
    }
    catch (char const* msg)
    {
        qInfo() << msg;
    }
}

void MainWindow::on_largeSpriteButton_clicked()
{
    try
    {
    QImage newSprite = sg.generatreNewSprite(SpriteSize::large);
    QGraphicsScene* scene = new QGraphicsScene();
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(newSprite).scaled(600,600));
    scene->addItem(item);

    ui->graphicsView->setScene(scene);
    }
    catch (char const* msg)
    {
        qInfo() << msg;
    }
}

void MainWindow::on_veryLargeSpriteButton_clicked()
{
    try
    {
    QImage newSprite = sg.generatreNewSprite(SpriteSize::veryLarge);
    QGraphicsScene* scene = new QGraphicsScene();
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(newSprite).scaled(600,600));
    scene->addItem(item);

    ui->graphicsView->setScene(scene);
    }
    catch (char const* msg)
    {
        qInfo() << msg;
    }
}
