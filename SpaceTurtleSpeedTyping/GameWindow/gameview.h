#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QWidget>
#include <SFML/Graphics.hpp>

namespace Ui {
class GameView;
}

class GameView : public QWidget
{
    Q_OBJECT

public:
    explicit GameView(QWidget *parent = nullptr);
    ~GameView();

signals:
    void homeClicked();

private slots:
    void on_endGameButton_clicked();

private:
    Ui::GameView *ui;
    sf::RenderTexture texture;
    sf::Texture sprite_texture;
    sf::Sprite sprite;
    QTimer *timer;


    void renderTexture();

};

#endif // GAMEVIEW_H
