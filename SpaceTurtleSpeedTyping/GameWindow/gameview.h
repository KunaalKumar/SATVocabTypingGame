#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QWidget>
#include <SFML/Graphics.hpp>
#include <QMediaPlayer>


namespace Ui {
class GameView;
}

class GameView : public QWidget
{
    Q_OBJECT

public:
    explicit GameView(QWidget *parent = nullptr);
    ~GameView();

    // Detect keyboard pressed event
    void keyPressEvent(QKeyEvent* event);

signals:
    void homeClicked();

private slots:


private:
    Ui::GameView *ui;
    int hitIdx;
    // Create a new render-texture
    sf::RenderTexture texture;
    sf::Texture sprite_texture;
    sf::Sprite sprite;
    sf::Font font;
    sf::Text text;
    QMediaPlayer fireSound;
    QVector<std::string> textVector;
    QTimer *timer;
    int count, firedms; // firedms determines the hit strike animation duration
    bool fired;

    void renderTexture();
    void fire(float x1, float y1, float x2, float y2);
    void endGame();

};

#endif // GAMEVIEW_H
