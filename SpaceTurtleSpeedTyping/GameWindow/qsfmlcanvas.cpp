#include "qsfmlcanvas.h"

#ifdef Q_WS_X11
#include <Qt/qx11info_x11.h>
#include <X11/Xlib.h>
#endif

QSFMLCanvas::QSFMLCanvas(QWidget *parent) : QWidget(parent), initialized(false)
{
    setAttribute(Qt::WA_PaintOnScreen);
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_NoSystemBackground);

    setFocusPolicy(Qt::StrongFocus);
}


void QSFMLCanvas::showEvent(QShowEvent*)
{
    if(!initialized)
    {
        // Under X11, we need to flush the commands sent to the server to ensure that
        // SFML will get an updated view of the windows
        #ifdef Q_WS_X11
            XFlush(QX11Info::display());
        #endif

        // Create the SFML window with the widget handle
        sf::RenderWindow::create(reinterpret_cast<sf::WindowHandle>(winId()));

        // Let the derived class do its specific stuff
        onInit();

        // Setup the timer to trigger a refresh at specified framerate
        connect(&timer, SIGNAL(timeout()), this, SLOT(repaint()));
        timer.start();
        initialized = true;
    }
}

QPaintEngine* QSFMLCanvas::paintEngine() const
{
    return 0;
}

void QSFMLCanvas::paintEvent(QPaintEvent*)
{
    RenderWindow::clear();
    onUpdate();
    RenderWindow::display();

}

void QSFMLCanvas::onInit()
{

}

void QSFMLCanvas::onUpdate()
{

}

QSFMLCanvas::~QSFMLCanvas()
{

}
