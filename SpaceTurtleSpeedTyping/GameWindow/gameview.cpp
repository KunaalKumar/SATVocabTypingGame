#include "gameview.h"
#include "ui_gameview.h"
#include <iostream>
#include <QDebug>
#include <QTimer>
#include <QKeyEvent>
#include <QtGui>


GameView::GameView(QWidget *parent) :
    ui(new Ui::GameView)
{
    ui->setupUi(this);
    lib.startRound();
    texture.create(720, 800);
    fireSound.setMedia(QUrl("qrc:/src/Sound/gun.wav"));
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GameView::renderTexture);
    timer->start(1);
}

GameView::~GameView()
{
    delete ui;
}

void GameView::renderTexture() {
    texture.clear(sf::Color::Black);

    refreshGameObjects(lib.getGameObject());

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

void GameView::refreshGameObjects(std::vector<GameObjects::GameObject *> v)
{
    lib.updateFrame();
    sf::Sprite sprite;
    sf::Sprite heart;
    for (auto *obj : v)
    {
        std::string type = obj->getTypeString();
        // use obj to determine what type of obj it is and
        // update their pos, image...etc
        sprite_texture.setSmooth(true);
        if (type == "player")
        {
            // For running and debugging on mac
            if(QSysInfo::productType() == "osx")
            {
                sprite_texture.loadFromFile("../../../../src/Images/cute_turtle.png");
                sprite_heart.loadFromFile("../../../../src/Images/full_heart.png");

                //font.loadFromFile("../../../../src/Fonts/PTZ56F.ttf");
            }
            else
            {
                sprite_texture.loadFromFile("../src/Images/cute_turtle.png");
                 sprite_heart.loadFromFile("../src/Images/full_heart.png");
                //font.loadFromFile("../src/Fonts/PTZ56F.ttf");
            }
            sprite_texture.setSmooth(true);
            sprite_heart.setSmooth(true);

            sprite.setTexture(sprite_texture);
            sprite.setPosition(std::get<0>(obj->getPos()), std::get<1>(obj->getPos()));
            texture.draw(sprite);

            heart.setTexture(sprite_heart);
            heart.setPosition(50, 50);
            texture.draw(heart);

        }
        else if (type == "enemy")
        {
            GameObjects::Enemy* enemy = (GameObjects::Enemy*) obj;
            //qDebug()<< "enemy made";
            sf::Text text;
            text.setFont(font);
            text.setCharacterSize(18);
            text.setString(enemy->getWord());
            text.setFillColor(sf::Color::White);
            if(QSysInfo::productType() == "osx")
            {
                font.loadFromFile("../../../../src/Fonts/PTZ56F.ttf");
            }
            else
            {
                font.loadFromFile("../src/Fonts/PTZ56F.ttf");
            }
            text.setPosition(std::get<0>(obj->getPos()), std::get<1>(obj->getPos()));
            texture.draw(text);
        }

    }
}


void GameView::keyPressEvent(QKeyEvent *event)
{
    char ch = static_cast<char>(event->key()+32);

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
