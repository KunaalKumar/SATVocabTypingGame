#include "objectcontroller.h"

ObjectController::ObjectController()
{
    // TODO: Generate all enemy images
    b2Vec2 gravity(0.0f, 0.0f);
    world = new b2World(gravity);

    // Initializing body defs
    enemyBodyDef.type = b2_dynamicBody;
    // TODO: Set starting position dynamically when creating enemy objects based on window size
    enemyBodyDef.position.Set(0,0);
    enemyBodyDef.angle = 0;
}

ObjectController::~ObjectController()
{
    delete targetedEnemy;
    delete player;
    delete world;
}

void ObjectController::createPlayer()
{
    // TO FIX: Position
    GameObjects::posTuple pos({0, 0});
    player = new GameObjects::Player(pos);
    objectsOnScreen.push_back(*player);
}

void ObjectController::createRoundOfEnemies(int round)
{
    LoadWords::createRoundWords(round);
}

void ObjectController::createEnemy(int round)
{
    // TODO: Box2D
    b2Body *enemyBody = world->CreateBody(&enemyBodyDef);
    b2PolygonShape boxShape;
    boxShape.SetAsBox(1,1);

    b2FixtureDef boxFixtureDef;
    boxFixtureDef.shape = &boxShape;
    boxFixtureDef.density = 1;

    enemyBody->CreateFixture(&boxFixtureDef);

    // TODO: EnemyImageGenerate

//     GameObjects::Enemy enemy(round, {0,0}, LoadWords::getWord());
    // load image
//    if (enemy.getWord() != "")
//    {
//        objectsOnScreen.push_back(enemy); /*adding comment for claification, calling the default connstructor of enemy will give a starting pos of 0,0
//                                                                          but a position can be specified by providing a tuple<unsigned int, usigned int> - which can be done with {,}*/
//        return enemy;
//    }
//    else
//    {
//        stopCreatingEnemies = true;
//    }
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
            targetedEnemy = nullptr;
            // TODO: create explosion
        }
    }

    // TODO: Box2D
    GameObjects::Projectile projectile({0,0});
    objectsOnScreen.push_back(projectile);
}

bool ObjectController::letterTyped(char letter)
{
    if (targetedEnemy == nullptr)
    {
        // shoot closest enemy with starting letter = letter
        double lowestDistance = DBL_MAX;
        for (unsigned int i = 0; i < objectsOnScreen.size(); i++)
        {
            if (objectsOnScreen[i]->isOfType(GameObjects::Type::enemy))
            {
                GameObjects::Enemy &enemy = static_cast<GameObjects::Enemy &>(objectsOnScreen[i]);
                if (enemy.startsWith(letter))
                {
                    double distance = enemy.distanceTo(player->getPos());

                    if (distance < lowestDistance)
                    {
                        lowestDistance = distance;

                        targetedEnemy = new GameObjects::TargetedEnemy(objectsOnScreen[i]);
                        objectsOnScreen[i] = targetedEnemy;
                    }
                }
            }
        }
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

void ObjectController::updateObjectPositions()
{
    // All body positions within world get updates after calling Step()
    world->Step(timeStep, velocityIterations, positionIterations);

    // TO FIX: Currently creating enemies every 2 seconds
    if (!stopCreatingEnemies && ++frameCounter % 2000 == 0)
    {
        // TO FIX: Currently round is constant 1
        createEnemy(1);
    }
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
