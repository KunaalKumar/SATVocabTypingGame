#include "objectcontroller.h"
#include <stdlib.h>
#include <QImageWriter>
#include <QImage>
#include <QString>
#include <QDebug>

ObjectController::ObjectController(int windowSizeX, int windowSizeY)
{
    this->windowSizeX = windowSizeX / 4;
    this->windowSizeY = windowSizeY / 4;

    frameCounter = 0;
    stopCreatingEnemies = false;
    explosion = nullptr;
    targetedEnemy = nullptr;

    LoadWords::importWords();
    initSpriteGenerator();
    initBox2DWorld();
    createPlayer();
}

ObjectController::~ObjectController()
{
    delete targetedEnemy;
    delete player;
    delete explosion;
    delete world;
}

void ObjectController::createPlayer()
{
    player = b2MakeNewPlayer();
    objectsOnScreen.push_back(player);
}

void ObjectController::createRoundOfEnemies(int round)
{
    createImagePaths();
    LoadWords::createRoundWords(round);
    stopCreatingEnemies = false;
}

void ObjectController::createEnemy(int round)
{
    std::string word = LoadWords::getWord();
    if (word != "")
    {
        GameObjects::Enemy *enemy = b2MakeNewEnemy(round, word);
        objectsOnScreen.push_back(enemy);
    }
    else
    {
        stopCreatingEnemies = true;
    }
}

void ObjectController::createProjectile()
{
    if (targetedEnemy == nullptr)
    {
        // miss
    }
    else
    {
        // hit

        if (targetedEnemy->wasDestroyed())
        {
            explosion = new GameObjects::Explosion(*targetedEnemy);
            // Remove this once BOX2D is finished
            //createExplosion();
            objectsOnScreen.erase(objectsOnScreen.begin() + targetedEnemy->getVectorIndex());
            delete targetedEnemy;
            targetedEnemy = nullptr;
        }
    }

    // TODO: Box2D
    //    GameObjects::Projectile projectile = new GameObjects::Projectile({0,0}, );
    //    objectsOnScreen.push_back(projectile);
}

void ObjectController::findNewTargetedEnemy(char letter)
{
    double lowestDistance = DBL_MAX;
    for (unsigned int i = 0; i < objectsOnScreen.size(); i++)
    {
        if (objectsOnScreen[i]->isOfType(GameObjects::Type::enemy))
        {
            GameObjects::Enemy enemy = *(static_cast<GameObjects::Enemy *>(objectsOnScreen[i]));
            double distance;

            if (enemy.startsWith(letter) && (distance = enemy.distanceTo(player->getPos())) < lowestDistance)
            {

                lowestDistance = distance;
                targetedEnemy = new GameObjects::TargetedEnemy(enemy, i);
                objectsOnScreen[i] = targetedEnemy;
                qDebug() << "target added";
            }
        }
    }
}

bool ObjectController::letterTyped(char letter)
{
    if (targetedEnemy == nullptr)
    {
        findNewTargetedEnemy(letter);
        if (targetedEnemy != nullptr)
        {

            targetedEnemy->shoot(letter);
        }
        createProjectile();
        return targetedEnemy == nullptr;
    }
    else
    {
        bool temp = targetedEnemy->shoot(letter);
        createProjectile();

        return temp;
    }
}

void ObjectController::createExplosion()
{
    objectsOnScreen[explosion->getVectorIndex()] = explosion;
}

void ObjectController::removeExplosion()
{
    objectsOnScreen.erase(objectsOnScreen.begin() + explosion->getVectorIndex());
    delete explosion;
    explosion = nullptr;
}

void ObjectController::updateObjectPositions()
{
    stepBox2DWorld();
    // TO FIX: Currently creating enemies every 5 seconds
    if (!stopCreatingEnemies && ++frameCounter == 100)
    {
        // TO FIX: Currently round is constant 1
        createEnemy(1);
        frameCounter = 0;

    }

    if (explosion != nullptr && explosion->getNumOfFrames() == 1000)
    {
        removeExplosion();
    }
}

const std::vector<GameObjects::GameObject *>& ObjectController::getObjects()
{
    return objectsOnScreen;
}

bool ObjectController::isEnemyKilled()
{
    return targetedEnemy == nullptr;
}

bool ObjectController::isRoundEnd()
{
    return targetedEnemy == nullptr && objectsOnScreen.size() == 1;
}

bool ObjectController::isEndGame()
{
    return player->getHealth() == 0;
}

// SPRITE_GENERATOR_STUFF

void ObjectController::initSpriteGenerator()
{
    QDir relativeDir(QDir::currentPath());
    relativeDir.cdUp();
    relativeDir.cd("../SpriteStructures/");
    sg = SpriteGenerator(relativeDir.path() + '/');
    imageCounter = 0;
}

void ObjectController::createImagePaths()
{
    enemyImagePathIndex = 0;
    for (int i = 0; i < 20; i++)
    {
        QImage sprite = sg.generatreNewSprite(SpriteSize::small);
        sprite.scaled(32, 32);

        std::string path = "../src/GImages/ss" + std::to_string(++imageCounter) + ".png";
        QString string = QString::fromStdString(path);
        QImageWriter writer(string, "png");

        if (writer.canWrite())
        {
            writer.write(sprite);
            imagePaths.push_back(path);
        }
        else
        {
            QImageWriter::ImageWriterError error = writer.error();
            QString strError = writer.errorString();
           // qDebug() << "ERROR" << strError;
        }

    }
}

//__________             ________  ________      _________ __          _____  _____
//\______   \ _______  __\_____  \ \______ \    /   _____//  |_ __ ___/ ____\/ ____\
// |    |  _//  _ \  \/  //  ____/  |    |  \   \_____  \\   __\  |  \   __\\   __\
// |    |   (  <_> >    </       \  |    `   \  /        \|  | |  |  /|  |   |  |
// |______  /\____/__/\_ \_______ \/_______  / /_______  /|__| |____/ |__|   |__|
//        \/            \/       \/        \/          \/

void ObjectController::initBox2DWorld() {
    // TODO: Generate all enemy images
    // TODO: make gravity an instance variable
    gravity = new b2Vec2(0, -100);
    world = new b2World(*gravity);

    // Initializing body defs
    enemyBodyDef.type = b2_dynamicBody;

    playerBodyDef.type = b2_staticBody;
}

b2Vec2 ObjectController::attractBToA(b2Body &bodyA, b2Body &bodyB)
{
    b2Vec2 posA = bodyA.GetWorldCenter();
    b2Vec2 posB = bodyB.GetWorldCenter();
    b2Vec2 force = posA - posB;
    float distance = force.Length();
    force.Normalize();
    float strength = (gravity->y * bodyA.GetMass() * bodyA.GetGravityScale() * 10000) / (distance * distance);
    force.operator*=(strength);
    return force;
}

void ObjectController::stepBox2DWorld()
{

    for(int i = 0; i < objectsOnScreen.size(); i++) {
        if(objectsOnScreen[i]->getTypeString() == "enemy") {
              objectsOnScreen[i]->getBody().ApplyLinearImpulseToCenter(
                          attractBToA(objectsOnScreen[i]->getBody(),
                                      player->getBody()), true);
        }
        else if (objectsOnScreen[i]->getTypeString() == "projectile") {
             GameObjects::Projectile projectile = *(static_cast<GameObjects::Projectile *>(objectsOnScreen[i]));
             if(projectile.getTargetBody() != nullptr) {
                 projectile.getBody().ApplyLinearImpulseToCenter(
                             attractBToA(projectile.getBody(),
                                         *projectile.getTargetBody()), true);
             }
             else {
                  // TODO :: apply miss impulse
             }
        }
    }

    // All body positions within world get updates after calling Step()
    world->Step(timeStep, velocityIterations, positionIterations);

    for(b2Contact *contact = world->GetContactList(); contact; contact = contact->GetNext()) {
        // TODO: Check for:
        //                  1) projectile contact with enemy body
        //                  2) enemy contact with player body
    }
}

GameObjects::Enemy *ObjectController::b2MakeNewEnemy(int round, std::string word)
{
    std::string imagePath = imagePaths.at(enemyImagePathIndex++);

    int boxSize = GameObjects::Enemy::getSize(word.size());
    enemyBodyDef.position.Set((rand() % (int)windowSizeX), 0);

    b2Body *enemyBody = world->CreateBody(&enemyBodyDef);
    b2PolygonShape boxShape;
    boxShape.SetAsBox(1, 1);

    b2FixtureDef boxFixtureDef;
    boxFixtureDef.shape = &boxShape;
    boxFixtureDef.density = 1;

    enemyBody->CreateFixture(&boxFixtureDef);

    GameObjects::Enemy *enemy = new GameObjects::Enemy(round, word, imagePath, boxSize, {enemyBodyDef.position.x, windowSizeY}, *enemyBody);
    enemyBody->SetUserData(enemy);

    // TODO: Make scale factor dynamic depending on enemy word length
    // Controls the speed of the enemy via proxy
    enemyBody->SetGravityScale(10000);

    return enemy;
}

GameObjects::Player *ObjectController::b2MakeNewPlayer()
{
    // Player position - 10% up from the bottom and in the middle of the screen
    playerBodyDef.position.Set((windowSizeX/2), -(0.9*windowSizeY));

    b2Body *playerBody = world->CreateBody(&playerBodyDef);
    b2PolygonShape boxShape;
    boxShape.SetAsBox(0, 0);

    b2FixtureDef boxFixtureDef;
    boxFixtureDef.shape = &boxShape;
    boxFixtureDef.density = 100000;

    playerBody->CreateFixture(&boxFixtureDef);

    GameObjects::Player *player = new GameObjects::Player({playerBodyDef.position.x, playerBodyDef.position.y}, *playerBody);

    playerBody->SetUserData(player);

    return player;
}

GameObjects::Projectile *ObjectController::b2MakeNewProjectile(b2Body &targetBody)
{
    playerBodyDef.position.Set(std::get<0>(player->getPos()),std::get<1>(player->getPos()));

    b2Body *projectileBody = world->CreateBody(&playerBodyDef);
    b2PolygonShape boxShape;
    boxShape.SetAsBox(1,1);

    b2FixtureDef boxFixtureDef;
    boxFixtureDef.shape = &boxShape;
    boxFixtureDef.density = 1;
    GameObjects::Projectile *projectile = new GameObjects::Projectile({playerBodyDef.position.x, playerBodyDef.position.y},
                                                                      *projectileBody, &targetBody);
    projectileBody->SetUserData(projectile);

    projectileBody->SetGravityScale(100);

    return projectile;
}
