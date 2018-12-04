/*
 * Purple Picnic Turtles
 *
 * Creator: - Soren Nelson
 *
 * spritanimation.cpp
 */

#include "spriteanimation.h"


SpriteAnimation::SpriteAnimation(std::vector<QImage*>* images)
{
    this->images = images;
}

void SpriteAnimation::setFrameRate(int rate)
{
    int oldRate = frameRate;
    frameRate = rate;
    frameIndex = 0;
    if (oldRate == 0)
    {
        QTimer::singleShot(0, this, SLOT(startAnimation()));
    }
}

void SpriteAnimation::startAnimation()
{
    if (images != nullptr && frameRate > 0 && images->size() > 0)
    {
       QTimer::singleShot((1000 / frameRate)/2, this, SLOT(displayFrame()));
    }
}

void SpriteAnimation::displayFrame()
{
    QImage  image   = *((*images)[frameIndex++ % images->size()]);
    QPixmap pixmap  = Global::convertImageToPixmap(image, 1);

    this->clear();
    this->addPixmap(pixmap);

    if (frameRate > 0)
    {
        QTimer::singleShot((1000 / frameRate)/2, this, SLOT(startAnimation()));
    }
}






