#include "gamewindow.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{

    qInfo() << sizeof (GameObjects::Projectile);
    QApplication a(argc, argv);
    GameWindow w;
    w.show();
    return a.exec();
}
