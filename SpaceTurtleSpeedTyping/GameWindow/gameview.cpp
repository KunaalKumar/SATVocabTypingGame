#include "gameview.h"
#include "ui_gameview.h"
#include <iostream>
#include <QDebug>
#include <QTimer>
#include <QKeyEvent>
#include <QtGui>


GameView::GameView(QWidget *parent) :
    ui(new Ui::GameView), lib(720, 800)
{
    ui->setupUi(this);
    lib.startRound();
    hitIdx = 0;
    fireSound.setMedia(QUrl("qrc:/src/Sound/gun.wav"));
    textVector.push_front("Hello");
    textVector.push_front("Hello");
    textVector.push_front("Hello");
    textVector.push_front("Hello");
    textVector.push_front("Hello");
    textVector.push_front("Hello");
    textVector.push_front("Hello");

    texture.create(720, 800);

    // For running and debugging on mac
    if(QSysInfo::productType() == "osx") {
        sprite_texture.loadFromFile("../../../../src/Images/cute_turtle.png");
        font.loadFromFile("../../../../src/Fonts/PTZ56F.ttf");
    }
    else {
        sprite_texture.loadFromFile("../src/Images/cute_turtle.png");
        font.loadFromFile("../src/Fonts/PTZ56F.ttf");
    }

    sprite_texture.setSmooth(true);
    // Create the sprite
    sprite.setTexture(sprite_texture);
    sprite.setPosition(328,700);

    text.setFont(font);
    text.setCharacterSize(18);
    text.setString("hello");
    text.setFillColor(sf::Color::White);
    count = 0;
    firedms = 0;
    fired = false;
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GameView::renderTexture);
    timer->start(100);
}

GameView::~GameView()
{
    delete ui;
}

void GameView::renderTexture() {
    texture.clear(sf::Color::Black);
    texture.draw(sprite);  // sprite is a sf::Sprite

//    for (int i = 0; i < textVector.size(); i++)
//    {
//        text.setString(textVector.at(i));
//        if (i == 0)
//            text.setPosition(15, count++);
//        else
//        {

//            text.setPosition(i * 100, count++);
//        }
//        if (count > 600) count = 0;
//        texture.draw(text);    // text is a sf::Text
//    }

    text.setPosition(100, count++);
    texture.draw(text);

    if (fired)
    {
        if (firedms++<6)
        {
            fire(328, 700, text.getPosition().x, text.getPosition().y);
        }
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


    QImage qi(pp, 720, 800, QImage::Format_ARGB32);
    qi = qi.rgbSwapped();

    ui->label->setPixmap(QPixmap::fromImage(qi));
}

void GameView::keyPressEvent(QKeyEvent *event)
{
    char ch = (char)(event->key()+32);
    if (!text.getString().find(ch))
    {

        fire(328, 700, text.getPosition().x, text.getPosition().y);
        text.setString(text.getString().substring(1));
    }


    if (event->key() == Qt::Key_Escape)
    {
        endGame();
    }
}

void GameView::fire(float x1, float y1, float x2, float y2)
{
    sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f(x1, y1)),
        sf::Vertex(sf::Vector2f(x2, y2))
    };

    fired = true;
    texture.draw(line, 2, sf::Lines);
    fireSound.play();
}

void GameView::endGame()
{
    qDebug()<< "End game signaled!";
    emit homeClicked();
}

