#ifndef MYRECT_H
#define MYRECT_H

#include <QGraphicsRectItem>

class MyRect : public QGraphicsRectItem
{
public:
    MyRect();
    void keyPressEvent(QKeyEvent *event);
    void moveRectBy(int i);
};

#endif // MYRECT_H
