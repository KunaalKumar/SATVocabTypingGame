#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "spritegenerator.h"
#include <QGraphicsScene>
#include "spritegenerator.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_smallSpriteButton_clicked();

    void on_mediumSprietButton_clicked();

    void on_largeSpriteButton_clicked();

    void on_veryLargeSpriteButton_clicked();

    void on_modularSpriteButton_clicked();

private:
    Ui::MainWindow *ui;
    SpriteGenerator sg;
};

#endif // MAINWINDOW_H
