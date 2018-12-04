/*
 * Purple Picnic Turtles
 *
 * Creator: - Soren Nelson
 *
 * spriteanimation.h
 */

#ifndef SPRITEANIMATION_H
#define SPRITEANIMATION_H

#include <QGraphicsScene>
#include <QPixmap>
#include <QTimer>
#include "global.h"


class SpriteAnimation: public QGraphicsScene
{
    Q_OBJECT

private:
    std::vector<QImage*>* images;
    int frameIndex;

private slots:
    void displayFrame();
    void startAnimation();

public:
    SpriteAnimation(std::vector<QImage*>* images);
    void setFrameRate(int rate);
};

#endif // SPRITEANIMATION_H
