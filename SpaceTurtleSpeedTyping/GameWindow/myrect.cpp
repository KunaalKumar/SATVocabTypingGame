#include "myrect.h"

MyRect::MyRect()
{
    setFlags(QGraphicsItem::ItemIsFocusable);
}

void MyRect::keyPressEvent(QKeyEvent *event)
{
    moveBy(x() + 10, y() - 10);

}

void MyRect::moveRectBy(int i)
{
    moveBy(i, 0);

}
