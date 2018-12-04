/*
 * Purple Picnic Turtles
 *
 * Creator: - Kunaal Kumar
 *
 * gridsizedialog.cpp
 */

#include "gridsizedialog.h"
#include "ui_gridsizedialog.h"
#include <global.h>
#include <cmath>

GridSizeDialog::GridSizeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GridSizeDialog)
{
    ui->setupUi(this);
}

GridSizeDialog::~GridSizeDialog()
{
    delete ui;
}

void GridSizeDialog::on_gridSizeSlider_valueChanged(int value)
{
    ui->gridSizeLabel->setText(QString::number(value));
    gridSize = value;
    int windowSizeFactor = std::ceil(600/value);
    windowSize = value*windowSizeFactor;
}

void GridSizeDialog::on_okButton_clicked()
{
    this->close();
}
