/*
 * Purple Picnic Turtles
 *
 * Creator: - Kunaal Kumar
 *
 * colorlabel.h
 */

#ifndef COLORLABEL_H
#define COLORLABEL_H

#include <QLabel>


class ColorLabel : public QLabel
{
    Q_OBJECT
public:
    ColorLabel(QWidget *parent = 0);

signals:
    void colorChanged(QColor color, ColorLabel* label);

protected:
    void mousePressEvent(QMouseEvent* event);
};

#endif // COLORLABEL_H
