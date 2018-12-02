#include "gameview.h"
#include "ui_gameview.h"
#include <iostream>
#include <QDebug>
#include <QTimer>

GameView::GameView(QWidget *parent) :
    ui(new Ui::GameView)
{
    ui->setupUi(this);
    // Size the texture
    texture.create(500, 400);
    sprite_texture.loadFromFile("/Users/wei-tungtang/Documents/A8-an-educational-app-f18-Purple-Picnic-Turtles-2.0/SpaceTurtleSpeedTyping/GameWindow/Images/test.png");
    sprite_texture.setSmooth(true);
    // Create the sprite
    sprite.setTexture(sprite_texture);

    sprite.setOrigin(200,100);
    sprite.setPosition(100,150);
    //    renderTexture();
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GameView::renderTexture);
    timer->start(1);
}

GameView::~GameView()
{
    delete ui;
}



void GameView::on_endGameButton_clicked()
{
    qDebug()<< "End game signaled!";
    emit homeClicked();
}

void GameView::renderTexture() {
    // Clear the whole texture with red color
    texture.clear(sf::Color::Red);
    sprite.rotate(1.0);
    // Draw stuff to the texture
    texture.draw(sprite);  // sprite is a sf::Sprite
//    texture.draw(shape);   // shape is a sf::Shape
//    texture.draw(text);    // text is a sf::Text
    // We're done drawing to the texture
    texture.display();

    // Set to a QImage
    sf::Texture rt = texture.getTexture();
    sf::Image irt = rt.copyToImage();
    const uint8_t *pp = irt.getPixelsPtr();

    QImage qi(pp, 500, 400, QImage::Format_ARGB32);
    qi = qi.rgbSwapped();

    ui->label->setPixmap(QPixmap::fromImage(qi));
}
