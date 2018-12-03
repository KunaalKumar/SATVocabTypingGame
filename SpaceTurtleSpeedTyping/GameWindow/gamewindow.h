#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

    // Detect keyboard pressed event
    void keyPressEvent(QKeyEvent* event);

private slots:

    // Game Start button action in starting screen.
    // Press the button will take the user to game page.
    void on_gameStartButton_clicked();

    // End Game button action in game page. Similar logic to
    // game start button action
    void on_endGameButton_clicked();

    void on_optionButton_clicked();

    void on_tutorialButton_clicked();

private:

    // This ui reference is composed of 2 pages enabled by the stackedWidget
    // by using stackedWidge's function - setCurrentIndex(index), we have a way
    // to navigate between these 2 pages.
    Ui::GameWindow *ui;

    // Create a new render-texture
    sf::RenderTexture texture;
    sf::Texture sprite_texture;
    sf::Sprite sprite;
    sf::Font font;
    sf::Text text;

    QTimer *timer;
    int count, firedms;
    bool fired;

    void renderTexture();
    void fire(float x1, float y1, float x2, float y2);
};

#endif // GAMEWINDOW_H
