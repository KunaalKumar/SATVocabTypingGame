/*
 * Purple Picnic Turtles
 *
 * Creator: - Kunaal Kumar
 *
 * canvas.h
 */

#ifndef CANVAS_H
#define CANVAS_H

#include <QPixmap>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include "global.h"


class Canvas  : public QGraphicsScene
{
    Q_OBJECT

    public:
        Canvas(int frameSize, QImage* image, QObject *parent = 0);

        virtual void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent);
        virtual void mouseMoveEvent(QGraphicsSceneMouseEvent * mouseEvent);
        virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * mouseEvent);

        void setImage(QImage* image);

        void toggleGridlines();

        void setNewFrameSize(int frameSize);

    signals:
        void mousePressed(int button, QPointF point);
        void mouseMoved(int button, QPointF point);
        void mouseReleased(int button, QPointF point);

    public slots:

    private:
        QPixmap pixmap;
        QImage* image;
        bool enableGridLines;
        int framePixelSize;

        QPointF convertToPoint(QPointF scaledPos);
        void updatePixmap();
};

#endif // CANVAS_H
