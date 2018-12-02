#ifndef QSFMLCANVAS_H
#define QSFMLCANVAS_H


#include <QObject>
#include <QWidget>
#include <QTimer>
#include <SFML/Graphics.hpp>

class QSFMLCanvas : public QWidget, public sf::RenderWindow
{
    Q_OBJECT
public:
    explicit QSFMLCanvas(QWidget *parent = nullptr);
    virtual QPaintEngine *paintEngine() const;
    virtual void showEvent(QShowEvent *event);
    virtual void paintEvent(QPaintEvent *event);
    virtual void onInit();
    virtual void onUpdate();
    virtual ~QSFMLCanvas();

private:
    QTimer timer;
    bool initialized;

signals:

public slots:
};

#endif // QSFMLCANVAS_H
