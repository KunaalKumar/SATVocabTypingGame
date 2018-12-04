/*
 * Purple Picnic Turtles
 *
 * Creator: - Nathan Boehm
 *
 * mainwindow.h
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QPixmap>
#include "project.h"
#include "frameview.h"


namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_toggleGridlinesButton_clicked();

    void on_horizontalSlider_valueChanged(int value);

    void on_penToolButton_clicked();

    void on_eraserToolButton_clicked();

    void on_brushToolButton_clicked();

    void on_lineToolButton_clicked();

    void on_fillToolButton_clicked();

    void initializeProject();

    void on_actionSave_triggered();

    void on_actionLoad_triggered();

    void on_actionExport_triggered();

    void on_frameTableWidget_cellClicked(int row, int column);

    void on_brushSizeSpinBox_valueChanged(int value);

    void on_eraserSizeSpinBox_valueChanged(int value);

private:
    Ui::MainWindow* ui;
    Project* project;
    void highlightButton(Global::Tool tool);

friend int main(int argc, char *argv[]);
};

#endif // MAINWINDOW_H
