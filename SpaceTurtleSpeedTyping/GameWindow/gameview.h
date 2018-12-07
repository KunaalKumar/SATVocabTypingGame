#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QWidget>
#include <SFML/Graphics.hpp>
#include <QMediaPlayer>
#include "gamelib.h"
#include "gameobjects.h"

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
    GameLib lib = GameLib(720, 800);

    int hitIdx;
    // Create a new render-texture
    sf::RenderTexture texture;

    sf::Texture sprite_texture;  //turtle
    sf::Texture sprite_heart; //heart

    sf::Font font;
    QMediaPlayer fireSound;
    QVector<std::string> textVector;
    QTimer *timer;
    int count, firedms; // firedms determines the hit strike animation duration
    bool fired;
    float pXpos;
    float pYpos;
    int x_pos;
    int word_count_in_screen = 5;
    int word_showed;

    void renderTexture();
    // Initialize all game objects information (position, words..etc)
    void refreshGameObjects(std::vector<GameObjects::GameObject *>);
    void fire(float x1, float y1, float x2, float y2);
    void endGame();

};

#endif // GAMEVIEW_H
