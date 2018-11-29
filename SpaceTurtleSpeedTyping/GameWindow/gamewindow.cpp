#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <QDebug>
#include <QKeyEvent>
#include <QMessageBox>
#include <iostream>
#include <QWidget>
#include "Box2D/Box2D.h"
#include <QVBoxLayout>
#include "myrect.h"
#include <QTimer>

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    displacement = 10;

//    simulateGravity();

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

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    rect = new MyRect();
    rect->setRect(0,0,100,100);
    scene->addItem(rect);
    rect->setFocus();
    ui->graphicsView->show();
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(moveRect()));
    timer->start(167);
    QTimer::singleShot(5000, this, SLOT(stopTimer()));

}

void GameWindow::moveRect() {

        qInfo() << "Moved";
        rect->moveRectBy(displacement);
//        rect->moveBy(rect->x() - displacement, rect->y());
}

void GameWindow::stopTimer()
{
    qInfo() << "Stopping timer";
    timer->stop();
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

void GameWindow::simulateGravity() {

    // Ignore, just for testing

    // Define the gravity vector.
    b2Vec2 gravity(0.0f, -10.0f);

    // Construct a world object, which will hold and simulate the rigid bodies.
    b2World world(gravity);

    // Define the ground body.
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -10.0f);

    // Call the body factory which allocates memory for the ground body
    // from a pool and creates the ground box shape (also from a pool).
    // The body is also added to the world.
    b2Body* groundBody = world.CreateBody(&groundBodyDef);

    // Define the ground box shape.
    b2PolygonShape groundBox;

    // The extents are the half-widths of the box.
    groundBox.SetAsBox(50.0f, 50.0f);

    // Add the ground fixture to the ground body.
    groundBody->CreateFixture(&groundBox, 0.0f);

    // Define the dynamic body. We set its position and call the body factory.
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f, 4.0f);
    b2Body* body = world.CreateBody(&bodyDef);

    // Define another box shape for our dynamic body.
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 1.0f);

    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;

    // Set the box density to be non-zero, so it will be dynamic.
    fixtureDef.density = 1.0f;

    // Override the default friction.
    fixtureDef.friction = 0.3f;

    // Add the shape to the body.
    body->CreateFixture(&fixtureDef);

    // Prepare for simulation. Typically we use a time step of 1/60 of a
    // second (60Hz) and 10 iterations. This provides a high quality simulation
    // in most game scenarios.
    float32 timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    // This is our little game loop.
    for (int32 i = 0; i < 60; ++i)
    {
        // Instruct the world to perform a single step of simulation.
        // It is generally best to keep the time step and iterations fixed.
        world.Step(timeStep, velocityIterations, positionIterations);

        // Now print the position and angle of the body.
        b2Vec2 position = body->GetPosition();
        float32 angle = body->GetAngle();

        QString posX = QString::fromStdString(std::to_string(position.x));
        QString posY = QString::fromStdString(std::to_string(position.y));
//        ui->gravityLabel->setText(ui->gravityLabel->text() + "\n(" + posX + ", " + posY + ")");
//        printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
    }
}
