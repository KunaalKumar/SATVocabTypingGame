#include "objectcontroller.h"
#include <stdlib.h>
#include <QImage>


ObjectController::ObjectController()
{
    // TODO: Generate all enemy images
    // TODO: make gravity an instance variable
    b2Vec2 gravity(0.0f, -1.0f);
    world = new b2World(gravity);

    // Initializing body defs
    enemyBodyDef.type = b2_dynamicBody;
    enemyBodyDef.angle = 0;

    playerBodyDef.type = b2_staticBody;
    playerBodyDef.angle = 0;

    stopCreatingEnemies = true;
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
    // Player position - 10% up from the bottom and in the middle of the screen
    playerBodyDef.position.Set((windowSizeX/2), -(0.9*windowSizeY));

    b2Body *playerBody = world->CreateBody(&playerBodyDef);
    b2PolygonShape boxShape;
    boxShape.SetAsBox(1,1);

    b2FixtureDef boxFixtureDef;
    boxFixtureDef.shape = &boxShape;
    boxFixtureDef.density = 1;

    playerBody->CreateFixture(&boxFixtureDef);

    player = new GameObjects::Player({playerBodyDef.position.x, playerBodyDef.position.y}, *playerBody);
    objectsOnScreen.push_back(player);
}

void ObjectController::createRoundOfEnemies(int round)
{
    LoadWords::createRoundWords(round);
    stopCreatingEnemies = false;
}

void ObjectController::createEnemy(int round)
{
    // Set starting position dynamically when creating enemy objects based on window size
    enemyBodyDef.position.Set((rand() % (int)windowSizeX*2) - windowSizeX, windowSizeY);

    b2Body *enemyBody = world->CreateBody(&enemyBodyDef);
    b2PolygonShape boxShape;
    boxShape.SetAsBox(1,1);

    b2FixtureDef boxFixtureDef;
    boxFixtureDef.shape = &boxShape;
    boxFixtureDef.density = 1;

    enemyBody->CreateFixture(&boxFixtureDef);

    // TODO: 1) Add image
    GameObjects::Enemy *enemy = new GameObjects::Enemy(round, LoadWords::getWord(), 0, QImage(), {enemyBodyDef.position.x, windowSizeY}, *enemyBody);
    if (enemy->getWord() != "")
    {
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
            delete targetedEnemy;
            targetedEnemy = nullptr;
        }
    }

    // TODO: Box2D
//    GameObjects::Projectile projectile = new GameObjects::Projectile({0,0}, );
//    objectsOnScreen.push_back(projectile);
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
        return targetedEnemy == nullptr;
    }
    else
    {
        return targetedEnemy->shoot(letter);
    }
}

void ObjectController::findNewTargetedEnemy(char letter)
{
    double lowestDistance = DBL_MAX;
    for (unsigned int i = 0; i < objectsOnScreen.size(); i++)
    {
        if (objectsOnScreen[i]->isOfType(GameObjects::Type::enemy))
        {
            GameObjects::Enemy enemy = *(static_cast<GameObjects::Enemy *>(objectsOnScreen[i]));
            if (enemy.startsWith(letter))
            {
                double distance = enemy.distanceTo(player->getPos());

                if (distance < lowestDistance)
                {
                    lowestDistance = distance;
                    targetedEnemy = new GameObjects::TargetedEnemy(enemy, i);
                    objectsOnScreen[i] = targetedEnemy;
                }
            }
        }
    }
}

void ObjectController::createExplosion()
{
    objectsOnScreen[explosion->getVectorIndex()] = explosion;
}

void ObjectController::updateObjectPositions()
{
    // All body positions within world get updates after calling Step()
    world->Step(timeStep, velocityIterations, positionIterations);

    // TO FIX: Currently creating enemies every 5 seconds
    if (!stopCreatingEnemies && ++frameCounter == 5000)
    {
        // TO FIX: Currently round is constant 1
        createEnemy(1);
        frameCounter = 0;
    }

    if (explosion != nullptr && explosion->getNumOfFrames() == 1000)
    {
        objectsOnScreen.erase(objectsOnScreen.begin() + explosion->getVectorIndex());
        delete explosion;
        explosion = nullptr;
    }
}

std::vector<GameObjects::GameObject *>& ObjectController::getObjects()
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

void ObjectController::attractAToB(b2Body &bodyA, b2Body &bodyB)
{
    b2Vec2 posA = bodyA.GetWorldCenter();
    b2Vec2 posB = bodyB.GetWorldCenter();
    b2Vec2 force = posA - posB;
    float distance = force.Length();
    force.Normalize();
    float strength = (-1.0f * bodyA.GetMass() * bodyB.GetMass()) / (distance * distance);
    force.operator*=(strength);
    bodyA.ApplyForce(force, bodyA.GetWorldCenter(), true);
}
