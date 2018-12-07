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
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GameView::renderTexture);
}

GameView::~GameView()
{
    delete ui;
    delete lib;
}

void GameView::renderTexture() {
    texture.clear(sf::Color::Black);
    refreshGameObjects(lib->getGameObject());

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
    lib->updateFrame();
    //qDebug() << "V size: " << v.size();
    for (auto *obj : v)
    {
        //std::string type = obj->getTypeString();
        // use obj to determine what type of obj it is and
        // update their pos, image...etc
        sprite_texture.setSmooth(true);
        if (obj->isOfType(GameObjects::Type::player))
        {
            sf::Sprite sprite;

            // For running and debugging on mac
            if(QSysInfo::productType() == "osx")
            {
                sprite_texture.loadFromFile("../../../../src/Images/cute_turtle.png");
                //sprite_heart.loadFromFile("../../../../src/Images/full_heart.png");

                //font.loadFromFile("../../../../src/Fonts/PTZ56F.ttf");
            }
            else
            {
                sprite_texture.loadFromFile("../src/Images/cute_turtle.png");
                //sprite_heart.loadFromFile("../src/Images/full_heart.png");
                //font.loadFromFile("../src/Fonts/PTZ56F.ttf");
            }
            sprite_texture.setSmooth(true);
            sprite_heart.setSmooth(true);

            sprite.setTexture(sprite_texture);
            sprite.setPosition(std::get<0>(obj->getPos()), std::get<1>(obj->getPos()));
            texture.draw(sprite);

            updatePlayerHealth(obj);

        }
        else if (obj->isOfType(GameObjects::Type::enemy))
        {
            GameObjects::Enemy* enemy = (GameObjects::Enemy*) obj;
            //qDebug()<< "enemy made";
            sf::Sprite sprite;
            sf::Text text;
            text.setFont(font);
            text.setCharacterSize(18);
            text.setString(enemy->getWord());
            text.setFillColor(sf::Color::White);
            if(QSysInfo::productType() == "osx")
            {
                sprite_texture.loadFromFile(obj->getImage());
                font.loadFromFile("../../../../src/Fonts/PTZ56F.ttf");
            }
            else
            {
                sprite_texture.loadFromFile(obj->getImage());
                font.loadFromFile("../src/Fonts/PTZ56F.ttf");
            }
            sprite_texture.setSmooth(true);
            sprite.setTexture(sprite_texture);
            sprite.setPosition(std::get<0>(obj->getPos()), std::get<1>(obj->getPos()));
            sprite.scale(6.f,6.f);
            //sprite.setColor(sf::Color::Red);
            texture.draw(sprite);
            text.setPosition(std::get<0>(obj->getPos()), std::get<1>(obj->getPos())+48);
            texture.draw(text);
        }
        else if (obj->isOfType(GameObjects::Type::targetedEnemy))
        {
            qDebug() <<"targeted!";
            GameObjects::TargetedEnemy* target = (GameObjects::TargetedEnemy*) obj;
            sf::Text text;
            text.setFont(font);
            text.setCharacterSize(18);
            std::string targetText = target->getWord().substr(target->getCurrentLetterPos(), target->getWord().size()-1);
            text.setString(targetText);
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
        else
        {
            sf::Sprite sprite;
            // For running and debugging on mac
            if(QSysInfo::productType() == "osx")
            {
                sprite_texture.loadFromFile("../../../../src/Images/cute_turtle.png");
            }
            else
            {
                sprite_texture.loadFromFile("../src/Images/cute_turtle.png");

            }
            sprite_texture.setSmooth(true);
            sprite_heart.setSmooth(true);

            sprite.setTexture(sprite_texture);
            sprite.setPosition(std::get<0>(obj->getPos()), std::get<1>(obj->getPos()));
            texture.draw(sprite);
        }

    }
}

void GameView::updatePlayerHealth(GameObjects::GameObject * obj)
{
    GameObjects::Player *player = (GameObjects::Player *) obj;

    for (unsigned int i = 0; i < player->getHealth(); i++)
    {
        sf::Sprite heart;
        sprite_heart.loadFromFile("../src/Images/full_heart.png");
        heart.setTexture(sprite_heart);
        sprite_heart.setSmooth(true);
        heart.setTexture(sprite_heart);
        heart.setPosition(50 + 20+i*30, 50);
        texture.draw(heart);
    }
}

void GameView::keyPressEvent(QKeyEvent *event)
{
    char ch = static_cast<char>(event->key()+32);

    if (lib->letterTyped(ch))
        //fireSound.play();
    if (event->key() == Qt::Key_Escape)
    {
        endGame();
    }
}

void GameView::startGame()
{
    lib = new GameLib(720, 800);
    lib->startRound();
    texture.create(720, 800);
    fireSound.setMedia(QUrl("qrc:/src/Sound/gun.wav"));
    timer->start(1);
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
    timer->stop();
    emit homeClicked();
}
