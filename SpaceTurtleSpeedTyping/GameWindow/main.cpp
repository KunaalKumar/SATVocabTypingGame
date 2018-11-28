#include "gamewindow.h"
#include <QApplication>
#include "Box2D/Box2D.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameWindow w;
    w.show();
    return a.exec();
}
