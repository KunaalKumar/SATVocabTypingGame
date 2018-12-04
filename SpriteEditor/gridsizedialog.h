/*
 * Purple Picnic Turtles
 *
 * Creator: - Kunaal Kumar
 *
 * gridsizedialog.h
 */
#ifndef GRIDSIZEDIALOG_H
#define GRIDSIZEDIALOG_H

#include <QDialog>


namespace Ui
{
class GridSizeDialog;
}

class GridSizeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GridSizeDialog(QWidget *parent = nullptr);
    ~GridSizeDialog();

private slots:
    void on_gridSizeSlider_valueChanged(int value);
    void on_okButton_clicked();

private:
    Ui::GridSizeDialog *ui;
};

#endif // GRIDSIZEDIALOG_H
