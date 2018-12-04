/*
 * Purple Picnic Turtles
 *
 * Creator: - Soren Nelson
 *
 * SimonLogic.h
 */

#ifndef FRAMETABLEWIDGET_H
#define FRAMETABLEWIDGET_H

#include <QTableWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include "global.h"


class FrameView
{
public:
    FrameView(QTableWidget* tableWidget, std::vector<QImage*>* images);
    void loadFrames();
    void addFrame();
    void updateFrame(int frame);

signals:
    int switchFrame();

private:
    QTableWidget* tableWidget;
    std::vector<QImage*>* images;
    int columnCount;

    void createNewFrameButton();
    void initialAddFrame();
    void setFrame(int column, QImage* image);

};

#endif // FRAMETABLEWIDGET_H
