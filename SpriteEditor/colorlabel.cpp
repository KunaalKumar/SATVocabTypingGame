/*
 * Purple Picnic Turtles
 *
 * Creator: - Kunaal Kumar
 *
 * colorlabel.cpp
 */

#include "colorlabel.h"
#include <QColorDialog>

ColorLabel::ColorLabel(QWidget* parent):
    QLabel (parent)
{

}

void ColorLabel::mousePressEvent(QMouseEvent* ev)
{
    QColorDialog colorDialog;
    QColor color = colorDialog.getColor();
    if(color != QColor::Invalid)
    {
        emit colorChanged(color, this);
    }
}
