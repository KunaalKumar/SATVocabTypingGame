#include "objectcontroller.h"
#include <stdlib.h>
#include <QImage>


ObjectController::ObjectController()
{
    // TODO: Generate all enemy images
    initBox2DWorld();
    createPlayer();
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
    player = b2MakeNewPlayer();
    objectsOnScreen.push_back(player);
}

void ObjectController::createRoundOfEnemies(int round)
{
    LoadWords::createRoundWords(round);
    stopCreatingEnemies = false;
}

void ObjectController::createEnemy(int round)
{
    GameObjects::Enemy *enemy = b2MakeNewEnemy(round);

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
    stepBox2DWorld();

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

//__________             ________  ________      _________ __          _____  _____
//\______   \ _______  __\_____  \ \______ \    /   _____//  |_ __ ___/ ____\/ ____\
// |    |  _//  _ \  \/  //  ____/  |    |  \   \_____  \\   __\  |  \   __\\   __\
// |    |   (  <_> >    </       \  |    `   \  /        \|  | |  |  /|  |   |  |
// |______  /\____/__/\_ \_______ \/_______  / /_______  /|__| |____/ |__|   |__|
//        \/            \/       \/        \/          \/

void ObjectController::initBox2DWorld() {
    // TODO: Generate all enemy images
    // TODO: make gravity an instance variable
    gravity = new b2Vec2(0.0f, -1.0f);
    world = new b2World(*gravity);

    // Initializing body defs
    enemyBodyDef.type = b2_dynamicBody;
    enemyBodyDef.angle = 0;

    playerBodyDef.type = b2_staticBody;
    playerBodyDef.angle = 0;
}

void ObjectController::attractAToB(b2Body &bodyA, b2Body &bodyB)
{
    b2Vec2 posA = bodyA.GetWorldCenter();
    b2Vec2 posB = bodyB.GetWorldCenter();
    b2Vec2 force = posA - posB;
    float distance = force.Length();
    force.Normalize();
    float strength = (gravity->y * bodyA.GetMass() * bodyB.GetMass()) / (distance * distance);
    force.operator*=(strength);
    bodyA.ApplyForce(force, bodyA.GetWorldCenter(), true);
}

void ObjectController::stepBox2DWorld()
{
    qInfo() << "\nBefore step ";
    printPlayerPos();
    // All body positions within world get updates after calling Step()
    world->Step(timeStep, velocityIterations, positionIterations);
    qInfo() << "\nAfter step ";
    printPlayerPos();

    for(b2Contact *contact = world->GetContactList(); contact; contact = contact->GetNext()) {
        // TODO: Check for:
        //                  1) projectile contact with enemy body
        //                  2) enemy contact with player body
    }
}

GameObjects::Enemy *ObjectController::b2MakeNewEnemy(int round)
{
    std::string word = LoadWords::getWord();
    int boxSize = GameObjects::Enemy::getSize(word.size());

    // Set starting position dynamically when creating enemy objects based on window size
    enemyBodyDef.position.Set((rand() % (int)windowSizeX*2) - windowSizeX, windowSizeY);

    b2Body *enemyBody = world->CreateBody(&enemyBodyDef);
    b2PolygonShape boxShape;
    boxShape.SetAsBox(boxSize, boxSize);

    b2FixtureDef boxFixtureDef;
    boxFixtureDef.shape = &boxShape;
    boxFixtureDef.density = 1;

    enemyBody->CreateFixture(&boxFixtureDef);

    // TODO: 1) Add image
    GameObjects::Enemy *enemy = new GameObjects::Enemy(round, word, boxSize, QImage(), {enemyBodyDef.position.x, windowSizeY}, *enemyBody);

    enemyBody->SetUserData(enemy);

    return enemy;
}

GameObjects::Player *ObjectController::b2MakeNewPlayer()
{
    // Player position - 10% up from the bottom and in the middle of the screen
    playerBodyDef.position.Set((windowSizeX/2), -(0.9*windowSizeY));

    b2Body *playerBody = world->CreateBody(&playerBodyDef);
    b2PolygonShape boxShape;
    boxShape.SetAsBox(32, 32);

    b2FixtureDef boxFixtureDef;
    boxFixtureDef.shape = &boxShape;
    boxFixtureDef.density = 1;

    playerBody->CreateFixture(&boxFixtureDef);

    GameObjects::Player *player = new GameObjects::Player({playerBodyDef.position.x, playerBodyDef.position.y}, *playerBody);

    playerBody->SetUserData(player);

    return player;
}

void ObjectController::printPlayerPos()
{
    qInfo() << "Player pos --> " << std::get<0>(player->getPos()) << ", " << std::get<1>(player->getPos());
}
