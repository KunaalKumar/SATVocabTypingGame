#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <QDebug>
#include <QKeyEvent>
#include "../GameLib/status.h"
#include <QMessageBox>
#include <iostream>
#include <QWidget>
#include "../GameLib/gamelib.h"
#include "Box2D/Box2D.h"
#include <QTimer>

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    this->setFixedSize(720, 660);

    // Size the texture
    texture.create(720, 660);
    sprite_texture.loadFromFile("../src/icon.png");
    sprite_texture.setSmooth(true);
    // Create the sprite
    sprite.setTexture(sprite_texture);

    sprite.setOrigin(300,100);
    sprite.setPosition(360,195);

    font.loadFromFile("../src/PT Serif Caption.ttf");
    text.setFont(font);
    text.setCharacterSize(18);
    text.setString("hello");
    text.setFillColor(sf::Color::White);
    count = 0;
    firedms = 0;
    fired = false;

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GameWindow::renderTexture);
    timer->start(1);
}

void GameWindow::renderTexture() {
    // Clear the whole texture with red color
    texture.clear(sf::Color::Black);
    sprite.rotate(1.0);

    // Draw stuff to the texture
    texture.draw(sprite);  // sprite is a sf::Sprite

    //texture.draw(shape);   // shape is a sf::Shape

    if (text.getString() < " ")
        text.setString("hello");

    text.setPosition(100, count++);
    if (count > 640) count = 0;
    texture.draw(text);    // text is a sf::Text

    if (fired)
    {
        if (firedms++<6)
            fire(380, 600, text.getPosition().x, text.getPosition().y+20);
        else
        {
            fired = false;
            firedms = 0;
        }
    }

    // We're done drawing to the texture
    texture.display();

    // Set to a QImage
    sf::Texture rt = texture.getTexture();
    sf::Image irt = rt.copyToImage();
    const uint8_t *pp = irt.getPixelsPtr();

    QImage qi(pp, 720, 660, QImage::Format_ARGB32);
    qi = qi.rgbSwapped();

    ui->label->setPixmap(QPixmap::fromImage(qi));
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::keyPressEvent(QKeyEvent *event)
{
    char ch = (char)(event->key()+32);
    if (!text.getString().find(ch))
    {
        fire(380, 600, text.getPosition().x, text.getPosition().y+20);
        text.setString(text.getString().substring(1));
    }

    // Only inside of the game screen we take keyboard inputs
    if (ui->stackedWidget->currentIndex() == 1)
        qDebug() << " Key Pressed: " << (char)event->key();
}

void GameWindow::fire(float x1, float y1, float x2, float y2)
{
    sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f(x1, y1)),
        sf::Vertex(sf::Vector2f(x2, y2))
    };

    fired = true;
    texture.draw(line, 2, sf::Lines);
}

void GameWindow::on_gameStartButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void GameWindow::on_endGameButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void GameWindow::on_tutorialButton_clicked()
{
    qDebug() << "tutorial button pressed";
    QMessageBox::StandardButton box = QMessageBox::information(this, "Tutorial", "This is toturial",                                                              QMessageBox::Ok, QMessageBox::NoButton);
}

void GameWindow::on_optionButton_clicked()
{
    qDebug() << "option button pressed";
    QMessageBox::StandardButton box = QMessageBox::information(this, "Option", "Back to Title",                                                              QMessageBox::Ok, QMessageBox::NoButton);
}
