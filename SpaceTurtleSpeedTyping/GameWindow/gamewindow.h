#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsItem>

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
    QGraphicsItem *obj;
    QGraphicsScene *scene;
    void simulateGravity();
};

#endif // GAMEWINDOW_H
