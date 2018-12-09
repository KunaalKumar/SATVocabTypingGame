#include "gameview.h"
#include "ui_gameview.h"
#include <iostream>
#include <QTimer>
#include <QKeyEvent>
#include <QtGui>

GameView::GameView(QWidget *parent) :
    ui(new Ui::GameView)
{
    ui->setupUi(this);
    font.loadFromFile("../src/Fonts/Avenir.otf");
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
    if (!lib->isEndGame())
    {
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
        if (lib->isEndRound())
        {
            endRound();
        }

    }
    else
    {
        endRound();
    }


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
            sf::Sprite sprite;
            sf::Text text;
//            int rotation = ((enemy->getRotation(lib->getPlayer()) * 180) / 3.14);
//            rotation < 0 ? rotation -= 90 : rotation += 90;
//            sprite.rotate(rotation);
            text.setFont(font);
            text.setCharacterSize(18);
            text.setString(enemy->getWord());
            text.setFillColor(sf::Color::White);

            sprite_texture.loadFromFile(obj->getImage());

            sprite_texture.setSmooth(true);
            sprite.setTexture(sprite_texture);
            sprite.setPosition(std::get<0>(obj->getPos()), std::get<1>(obj->getPos()));
            //sprite.scale(6.f,6.f);
            texture.draw(sprite);
            text.setPosition(std::get<0>(obj->getPos()), std::get<1>(obj->getPos())+80);
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
            text.setFillColor(sf::Color::Red);

            sprite_texture.loadFromFile(obj->getImage());

            sprite_texture.setSmooth(true);
            sprite.setTexture(sprite_texture);
            sprite.setPosition(std::get<0>(obj->getPos()), std::get<1>(obj->getPos()));
            //sprite.scale(6.f,6.f);
            text.setPosition(std::get<0>(obj->getPos()), std::get<1>(obj->getPos())+80);
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
    if (player->getHealth() > 0)
    {
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
    else
    {
        lib->resetGame();
    }

}

void GameView::keyPressEvent(QKeyEvent *event)
{
    mutex.lock();
    char ch = static_cast<char>(event->key()+32);

    if (event->key() == Qt::Key_Escape)
    {
        endGame();
    }
    else
    {
        lib->letterTyped(ch);
    }

    mutex.unlock();
}

void GameView::startGame()
{
    lib = new GameLib(720, 800, false);
    fireSound.setMedia(QUrl("qrc:/src/Sound/gun.wav"));
    startRound();
}

void GameView::satGame()
{
    lib = new GameLib(720, 800, true);
    fireSound.setMedia(QUrl("qrc:/src/Sound/gun.wav"));
    startRound();
}

void GameView::startRound()
{
    lib->startRound();
    texture.create(720, 800);
    timer->start(10);
}

void GameView::endRound()
{
    timer->stop();
    displayStats();
}

void GameView::displayStats()
{
    texture.clear(sf::Color::Black);

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(25);

    std::string targetText = "Round : " + std::to_string((int)lib->getStatRound());
    text.setString(targetText);
    text.setFillColor(sf::Color::White);
    text.setPosition(250,300);
    texture.draw(text);

    targetText = "Total Kills : " + std::to_string((int)lib->getStatTotalScore());
    text.setString(targetText);
    text.setPosition(250,350);
    texture.draw(text);

    targetText = "Percentage Hit : " + std::to_string((int)lib->getStatHitRate()) + "%";
    text.setString(targetText);
    text.setPosition(250,400);
    texture.draw(text);

    targetText = "KillStreak : " + std::to_string((int)lib->getStatKillStreak());
    text.setString(targetText);
    text.setPosition(250,450);
    texture.draw(text);

    texture.display();

    sf::Texture rt = texture.getTexture();
    sf::Image irt = rt.copyToImage();
    const uint8_t *pp = irt.getPixelsPtr();
    QImage qi(pp, 720, 800, QImage::Format_ARGB32);
    qi = qi.rgbSwapped();

    ui->label->setPixmap(QPixmap::fromImage(qi));

   QTimer::singleShot(4000, this, SLOT(endDisplayStats()));

}

void GameView::endDisplayStats()
{
    if (lib->isEndGame())
    {
        endGame();
    }
    else
    {
        startRound();
    }
}

void GameView::endGame()
{
    if (timer->isActive())
    {
        timer->stop();
    }
    lib->resetGame();
    emit homeClicked();
}
