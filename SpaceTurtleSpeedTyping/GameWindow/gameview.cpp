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
    font.loadFromFile("../src/Fonts/PTZ56F.ttf");
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GameView::renderTexture);
}

GameView::~GameView()
{
    delete ui;
    delete lib;
}

void GameView::renderTexture() {
    if(!mutex.tryLock()) {
        return;
    }
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

    mutex.unlock();
}

void GameView::refreshGameObjects(std::vector<GameObjects::GameObject *> v)
{
    lib->updateFrame();
    for (auto *obj : v)
    {
        //std::string type = obj->getTypeString();
        // use obj to determine what type of obj it is and
        // update their pos, image...etc

        sprite_texture.setSmooth(true);
        if (obj->isOfType(GameObjects::Type::player))
        {
            sf::Sprite sprite;
            sprite_texture.loadFromFile("../src/Images/cute_turtle.png");
            sprite_texture.setSmooth(true);
            sprite_heart.setSmooth(true);
            sprite.setTexture(sprite_texture);
            sprite.setPosition(std::get<0>(obj->getPos()), std::get<1>(obj->getPos()));
            texture.draw(sprite);
            updatePlayerHealth(obj);

        }
        else if (obj->isOfType(GameObjects::Type::enemy))
        {
            GameObjects::Enemy* enemy = static_cast<GameObjects::Enemy*>(obj);
            //qDebug()<< "enemy made";
            sf::Sprite sprite;
            sf::Text text;
            text.setFont(font);
            text.setCharacterSize(18);
            text.setString(enemy->getWord());
            text.setFillColor(sf::Color::White);

            sprite_texture.loadFromFile(obj->getImage());

            sprite_texture.setSmooth(true);
            sprite.setTexture(sprite_texture);
            sprite.setPosition(std::get<0>(obj->getPos()), std::get<1>(obj->getPos()));
            sprite.scale(6.f,6.f);
            texture.draw(sprite);
            text.setPosition(std::get<0>(obj->getPos()), std::get<1>(obj->getPos())+48);
            texture.draw(text);
        }
        else if (obj->isOfType(GameObjects::Type::targetedEnemy))
        {
            GameObjects::TargetedEnemy* target = static_cast<GameObjects::TargetedEnemy*>(obj);
            sf::Sprite sprite;
            sf::Text text;
            text.setFont(font);
            text.setCharacterSize(24);
            std::string targetText = target->getWord().substr(target->getCurrentLetterPos(), target->getWord().size());
            text.setString(targetText);
            text.setFillColor(sf::Color::Yellow);

            sprite_texture.loadFromFile(obj->getImage());

            sprite_texture.setSmooth(true);
            sprite.setTexture(sprite_texture);
            sprite.setPosition(std::get<0>(obj->getPos()), std::get<1>(obj->getPos()));
            sprite.scale(6.f,6.f);
            text.setPosition(std::get<0>(obj->getPos()), std::get<1>(obj->getPos())+48);
            texture.draw(sprite);
            //texture.draw(background, text.getTransform());
            texture.draw(text);
        }
        else if (obj->isOfType(GameObjects::Type::projectile))
        {
            sf::Sprite sprite;
            GameObjects::Projectile *projectile = static_cast<GameObjects::Projectile*>(obj);
            if(projectile->getKillShot()) {
                sprite_texture.loadFromFile("../src/Images/Red_Projectile.png");
            }
            else {
                sprite_texture.loadFromFile("../src/Images/Blue_Projectile.png");
            }
            sprite_texture.setSmooth(true);
            sprite.setTexture(sprite_texture);
            sprite.setPosition(std::get<0>(projectile->getPos()), std::get<1>(projectile->getPos()));
            texture.draw(sprite);
        }
        else
        {
            sf::Sprite sprite;
            sprite_texture.loadFromFile("../src/Images/Explosion.png");
            sprite_texture.setSmooth(true);
            sprite.setTexture(sprite_texture);
            GameObjects::Explosion *explosion = static_cast<GameObjects::Explosion*>(obj);
            sprite.setPosition(std::get<0>(explosion->getPos()), std::get<1>(explosion->getPos()));
            texture.draw(sprite);
        }
    }
}

void GameView::updatePlayerHealth(GameObjects::GameObject * obj)
{
    GameObjects::Player *player =  static_cast<GameObjects::Player*>(obj);
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(18);
    std::string targetText = "Total Kills : " + std::to_string(static_cast<int>(lib->getStatTotalScore()));
    text.setString(targetText);
    text.setFillColor(sf::Color::White);
    text.setPosition(500,30);
    texture.draw(text);
    targetText = "Round : " + std::to_string(static_cast<int>(lib->getStatRound()));
    text.setString(targetText);
    text.setPosition(500,50);
    texture.draw(text);

    for (int i = 0; i < player->getHealth(); i++)
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
    mutex.lock();
    char ch = static_cast<char>(event->key()+32);

    if (lib->letterTyped(ch))
        //fireSound.play();
        if (event->key() == Qt::Key_Escape)
        {
            endGame();
        }
    mutex.unlock();
}

void GameView::startGame()
{
    lib = new GameLib(720, 800);
    lib->startRound();
    texture.create(720, 800);
    fireSound.setMedia(QUrl("qrc:/src/Sound/gun.wav"));
    timer->start(10);
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
