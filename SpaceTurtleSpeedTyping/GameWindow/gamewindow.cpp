#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <QDebug>
#include <QKeyEvent>
#include <QMessageBox>
#include <iostream>
#include <QWidget>
#include <QVBoxLayout>
#include <QTimer>


GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);

    sf::RenderTexture texture;
    texture.create(500, 400);
    sprite_texture.loadFromFile("/home/willtang/Desktop/icon.png");
    sprite_texture.setSmooth(true);
    // Create the sprite
    sprite.setTexture(sprite_texture);

    sprite.setOrigin(200,100);
    sprite.setPosition(100,150);
//    renderTexture();
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GameWindow::renderTexture);
    timer->start(1);

}

void GameWindow::renderTexture() {
    // Clear the whole texture with red colorPaintSFMLTextureWindow
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
GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::keyPressEvent(QKeyEvent *event)
{
    // Only inside of the game screen we take keyboard inputs
    if (ui->stackedWidget->currentIndex() == 1)
        qDebug() << " Key Pressed: " << (char)event->key();
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

