/*
 * Purple Picnic Turtles
 *
 * Creator: - Kunaal Kumar
 *
 * SimonLogic.h
 */

#ifndef GLOBAL_H
#define GLOBAL_H

#include <QPixmap>
#include <QtDebug>


extern int windowSize;
extern int gridSize;
extern int frameRate;

namespace Global
{
    static int animationWindowSize = 295;
    static int frameWindowSize = 150;

    static QPixmap convertImageToPixmap(QImage image, int window)
    {
        if (window == 0)
        {
            return QPixmap().fromImage(image.scaled(windowSize, windowSize));
        }
        else if (window == 1)
        {
            return QPixmap().fromImage(image.scaled(animationWindowSize, animationWindowSize));
        }
        return QPixmap().fromImage(image.scaled(frameWindowSize, frameWindowSize));

    }

    static QPixmap convertImageToPixmapWithGridLines(QImage image, int gridPixelSize = gridSize)
    {
           QImage scaledImage = image.scaled(windowSize, windowSize);

           for(int x = 0; x < windowSize; x++)
           {
               // Vertical
               if((x % (windowSize / gridPixelSize)) == 0)
               {
                   for(int y = 0; y < windowSize; y++)
                   {
                       scaledImage.setPixelColor(x, y, QColor(0, 0, 0).rgba());
                   }
               }

               // Horizontal
               for(int y = 0; y < windowSize; y+=(windowSize/ gridPixelSize))
               {
                   scaledImage.setPixelColor(x, y, QColor(0, 0, 0).rgba());
               }
           }

           return QPixmap().fromImage(scaledImage);
      }

    const QString buttonHighlightFormat = QString("background-color: %1").arg(QColor(Qt::green).name());
    const QString buttonNonHighlightFormat = QString("background-color: %1; color: %2;").arg(QColor(Qt::black).name(), QColor(Qt::white).name());

    enum class Tool
    {
        pen,
        eraser,
        line,
        fill,
        brush,
    };
}

#endif // GLOBAL_H
