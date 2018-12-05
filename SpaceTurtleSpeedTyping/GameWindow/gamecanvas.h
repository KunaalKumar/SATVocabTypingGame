#ifndef GAMECANVAS_H
#define GAMECANVAS_H

#include <QObject>
#include <QWidget>
#include <qsfmlcanvas.h>

class GameCanvas: public QWidget, public QSFMLCanvas
{
public:
    GameCanvas(QWidget *parent = nullptr);
};

#endif // GAMECANVAS_H
