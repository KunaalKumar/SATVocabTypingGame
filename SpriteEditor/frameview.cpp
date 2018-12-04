/*
 * Purple Picnic Turtles
 *
 * Creator: - Soren Nelson
 *
 * frameview.cpp
 */

#include "frameview.h"


FrameView::FrameView(QTableWidget* tableWidget, std::vector<QImage*>* images)
{
    this->images = images;
    this->columnCount = 0;
    this->tableWidget = tableWidget;

    this->tableWidget->setRowCount(1);
    this->tableWidget->setRowHeight(0, tableWidget->height());

    createNewFrameButton();
    for (int i = 0; i < images->size(); i++)
    {
        initialAddFrame();
    }
}

void FrameView::createNewFrameButton()
{
    tableWidget->setColumnCount(++columnCount);
    tableWidget->setColumnWidth(columnCount - 1, 150);
    setFrame(0, new QImage(":/src/src/add.png"));
}

void FrameView::initialAddFrame()
{
    tableWidget->setColumnCount(++columnCount);
    tableWidget->setColumnWidth(columnCount - 1, 150);
    setFrame(columnCount - 1, images->at(columnCount - 2));
    tableWidget->selectColumn(columnCount - 1);
}

void FrameView::addFrame()
{
    tableWidget->setColumnCount(++columnCount);
    tableWidget->setColumnWidth(columnCount - 1, 150);

    setFrame(columnCount - 1, images->at(columnCount - 2));
    tableWidget->selectColumn(columnCount - 1);
}

void FrameView::setFrame(int column, QImage* image)
{
    QTableWidgetItem* item = new QTableWidgetItem;
    QPixmap pixmap = Global::convertImageToPixmap(*image, 2);
    QIcon icon(pixmap);
    item->setIcon(icon);
    tableWidget->setItem(0, column, item);
    tableWidget->setIconSize(QSize(145, 145));
    tableWidget->show();
}

void FrameView::updateFrame(int frame)
{
    setFrame(frame + 1, images->at(frame));
}

void FrameView::loadFrames()
{
    columnCount = 1;
    for (int i = 0; i < images->size(); i++)
    {
        initialAddFrame();
    }
}

