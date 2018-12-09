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
    playerExplosion = nullptr;
    enemyExplosion = nullptr;
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
    delete enemyExplosion;
    delete playerExplosion;
    delete world;
}

/**
 * @brief ObjectController::createPlayer
 * Called at beginning of game
 */
void ObjectController::createPlayer()
{
    player = b2MakeNewPlayer();
    objectsOnScreen.push_back(player);
}

/**
 * @brief ObjectController::createRoundOfEnemies
 * Called at beginning of round
 *
 * @param round
 */
void ObjectController::createRoundOfEnemies(int round)
{
    this->round = round;
    createImagePaths();
    LoadWords::createRoundWords(round);
    stopCreatingEnemies = false;
}

/**
 * @brief ObjectController::createEnemy
 * Called every 100 frames if there are still enemies to be created
 */
void ObjectController::createEnemy()
{
    std::string word = LoadWords::getWord();
    bool endOfRound = word == "";
    if (!endOfRound)
    {
        GameObjects::Enemy *enemy = b2MakeNewEnemy(this->round, word);
        objectsOnScreen.push_back(enemy);
    }
    else
    {
        stopCreatingEnemies = true;
    }
}

/**
 * @brief ObjectController::updateObjectPositions
 *  Called every frame by GameLib
 *  Updates everything in Box2D
 *  Creates Enemies when needed
 *  Removes Explosions when needed
 */
void ObjectController::updateObjectPositions()
{
    stepBox2DWorld();

    // Create Enemy Timer
    if (!stopCreatingEnemies && ++frameCounter == 100)
    {
        // TO FIX: Currently round is constant 1
        createEnemy();
        frameCounter = 0;
    }

    // End of enemyExplosion Timer
    if (enemyExplosion != nullptr && enemyExplosion->getNumOfFrames() == 150)
    {
        removeEnemyExplosion();
    }

    // End of playerExplosion Timer
    if (playerExplosion != nullptr && playerExplosion->getNumOfFrames() == 150)
    {
        removePlayerExplosion();
    }
}

/**
 * @brief ObjectController::letterTyped
 * Called from Gamelib when letter is typed on fronted
 * Targets new enemy || checks if letter typed is correct on target
 *
 * @param letter
 * @return Whether enemy was hit
 */
bool ObjectController::letterTyped(char letter)
{
    bool noCurrentTargetedEnemy = targetedEnemy == nullptr;
    if (noCurrentTargetedEnemy)
    {
        findNewTargetedEnemy(letter);

        bool hit = false;
        bool foundTargetEnemy = targetedEnemy != nullptr;
        if (foundTargetEnemy)
        {
            hit = targetedEnemy->shoot(letter);
        }

        createProjectile(hit);
        return foundTargetEnemy;
    }
    else
    {
        bool hit = targetedEnemy->shoot(letter);
        createProjectile(true);
        if (!hit)
        {
            targetedEnemy->resetWord();
        }
        return hit;
    }
}

/**
 * @brief ObjectController::findNewTargetedEnemy
 * Called inside letterTyped() when there is no targetedEnemy
 * Sets targetedEnemy and adds to objectsOnScreen if the letter == an enemy's first letter
 *
 * @param letter
 */
void ObjectController::findNewTargetedEnemy(char letter)
{
    double lowestDistance = DBL_MAX;
    unsigned int index = 0;
    GameObjects::TargetedEnemy *tempTarget = nullptr;

    // Finds the closest enemy with letter == enemy's firstLetter
    for (unsigned int i = 0; i < objectsOnScreen.size(); i++)
    {
        if (objectsOnScreen[i]->isOfType(GameObjects::Type::enemy))
        {
            GameObjects::Enemy enemy = *(static_cast<GameObjects::Enemy *>(objectsOnScreen[i]));
            double distance = 0.0;

            if (enemy.startsWith(letter) && (distance = enemy.distanceTo(player->getPos())) < lowestDistance)
            {
                lowestDistance = distance;
                tempTarget = new GameObjects::TargetedEnemy(enemy);
                index = i;
            }
        }
    }

    bool foundNewTarget = tempTarget != nullptr;
    if (foundNewTarget)
    {
        targetedEnemy = tempTarget;
        objectsOnScreen[index] = targetedEnemy;
    }
}

/**
 * @brief ObjectController::createProjectile
 * Called when correct letter is typed inside oc.letterTyped()
 *
 * @param hitEnemy
 */
void ObjectController::createProjectile(bool hitEnemy)
{
    if (!hitEnemy)
    {
        // make miss projectile
        objectsOnScreen.push_back(b2MakeNewProjectile(nullptr, false));
    }
    else
    {
        // create killshot projectile
        if (targetedEnemy->wasDestroyed())
        {
            objectsOnScreen.push_back(b2MakeNewProjectile(targetedEnemy->getBody(), true));

            // reset targetedEnemy so you can find new one
            // not removed from objectsOnScreen because frontend will still need to display until hit by projectile
            targetedEnemy = nullptr;
        }
        else
        {
            // create hit projectile (not a kill)
            objectsOnScreen.push_back(b2MakeNewProjectile(targetedEnemy->getBody(), false));
        }
    }
}

/**
 * @brief ObjectController::createPlayerExplosion
 * Called when b2d detects an enemy hit player
 *
 * @param enemyObject : enemy that hit player
 */
void ObjectController::createPlayerExplosion(GameObjects::GameObject *enemyObject)
{
    // remove one heart as player takes one hit
    player->removeHealth();
    // remove Enemy that hits player
    for(int i = 0 ; i < objectsOnScreen.size(); i++) {
        if(objectsOnScreen[i] == enemyObject) {
            world->DestroyBody(objectsOnScreen[i]->getBody());
            objectsOnScreen.erase(objectsOnScreen.begin() + i);
            break;
        }
    }
    // remove targeted enemy if it was the enemy
    if (enemyObject == targetedEnemy)
    {
        targetedEnemy = nullptr;
    }

    // If there is an old player explosion, remove it
    removeOldPlayerExplosion();
    playerExplosion = new GameObjects::Explosion(player->getPos());
    objectsOnScreen.push_back(playerExplosion);
}

/**
 * @brief ObjectController::removePlayerExplosion
 * Called when player explosion has been on screen 500 frames
 */
void ObjectController::removePlayerExplosion()
{
    int index = findIndexOfType(GameObjects::Type::explosion, playerExplosion);
    objectsOnScreen.erase(objectsOnScreen.begin() + index);

    //delete playerExplosion;
    playerExplosion = nullptr;
}

/**
 * @brief ObjectController::createEnemyExplosion
 * Called when b2d detects an projectile hit enemy
 *
 * @param projectileObject : projectile that hit enemy
 */
void ObjectController::createEnemyExplosion(GameObjects::GameObject *projectileObject)
{
    // Remove old targeted enemy
    int index = findOldTargetedEnemy();
    GameObjects::posTuple oldTargetedEnemyPosition = objectsOnScreen[index]->getPos();
    qDebug() << "Delete: " << index;
    world->DestroyBody(objectsOnScreen[index]->getBody());
    //delete objectsOnScreen[index];
    objectsOnScreen.erase(objectsOnScreen.begin() + index);

    // If there is an old enemy explosion, remove it
    removeOldEnemyExplosion();
    enemyExplosion = new GameObjects::Explosion(oldTargetedEnemyPosition);
    objectsOnScreen.push_back(enemyExplosion);

    // Remove Projectile that hit enemy
    index = findIndexOfType(GameObjects::Type::projectile, projectileObject);
    world->DestroyBody(objectsOnScreen[index]->getBody());
    //delete objectsOnScreen[index];
    objectsOnScreen.erase(objectsOnScreen.begin() + index);
}

/**
 * @brief ObjectController::removeEnemyExplosion
 * Called when enemy explosion has been on screen 500 frames
 *
 */
void ObjectController::removeEnemyExplosion()
{
    int index = findIndexOfType(GameObjects::Type::explosion, enemyExplosion);
    objectsOnScreen.erase(objectsOnScreen.begin() + index);

    //delete enemyExplosion;
    enemyExplosion = nullptr;
}

/**
 * @brief ObjectController::findIndexOfType
 * Finds the index of given type
 * If only type is passed in then finds first instance
 *
 * @param type
 * @param gameObject : default to nullptr
 * @return
 */
int ObjectController::findIndexOfType(GameObjects::Type type, GameObjects::GameObject *gameObject)
{
    int index = -1;
    for (GameObjects::GameObject *object : objectsOnScreen)
    {
        index++;
        if (object->isOfType(type))
        {
            if (gameObject != nullptr && gameObject == object)
            {
                break;
            }
            else if (gameObject == nullptr)
            {
                break;
            }
        }
    }
    return index;
}

/**
 * @brief ObjectController::findOldTargetedEnemy
 * Called by createEnemyExplosion
 * Instance of targetedEnemy may have changed if a new letter was typed
 * The object would be left in objectsOnScreen to display until the projectile collides with the enemy
 *
 * @return : -1 if no old targeted, index of old target otherwise
 */
int ObjectController::findOldTargetedEnemy()
{
    int index = -1;
    for (unsigned int i = 0; i < objectsOnScreen.size(); i ++)
    {
        GameObjects::GameObject *object = static_cast<GameObjects::GameObject *>(objectsOnScreen[i]);
        if (object->isOfType(GameObjects::Type::targetedEnemy))
        {
            bool noTargetedEnemy = targetedEnemy == nullptr;
            bool notNewTargetedEnemy = !noTargetedEnemy && targetedEnemy != object;

            if (notNewTargetedEnemy || noTargetedEnemy)
            {
                index = i;
                 qDebug() << index;
                break;
            }
        }
    }

    return index;
}

/**
 * @brief ObjectController::removeOldEnemyExplosion
 * Called by createEnemyExplosion
 * Removes explosion if there is an old one
 */
void ObjectController::removeOldEnemyExplosion()
{
    if (enemyExplosion != nullptr)
    {
        int index = findIndexOfType(GameObjects::Type::explosion, enemyExplosion);
        //delete objectsOnScreen[index];
        objectsOnScreen.erase(objectsOnScreen.begin() + index);
    }
}

/**
 * @brief ObjectController::removeOldPlayerExplosion
 * Called by createPlayerExplosion
 * Removes explosion if there is an old one
 */
void ObjectController::removeOldPlayerExplosion()
{
    if (playerExplosion != nullptr)
    {
        int index = findIndexOfType(GameObjects::Type::explosion, playerExplosion);
        //delete objectsOnScreen[index];
        objectsOnScreen.erase(objectsOnScreen.begin() + index);
    }
}

/**
 * @brief ObjectController::removeObjectAndDestroyBody
 * Called when projectile is not a killshot
 *
 * @param obj
 */
void ObjectController::removeObjectAndDestroyBody(GameObjects::GameObject *obj)
{
    if(obj->getBody() != nullptr) {
        world->DestroyBody(obj->getBody());
    }

    objectsOnScreen.erase(std::remove(objectsOnScreen.begin(),
                                      objectsOnScreen.end(),
                                      obj),
                            objectsOnScreen.end());
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
        QImage sprite = sg.generatreNewSprite(SpriteSize::modular);
        sprite = sprite.scaled(32, 96);

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
    gravity = new b2Vec2(0, -10);
    world = new b2World(*gravity);
//    world->SetAllowSleeping(false);
}

b2Vec2 ObjectController::attractBToA(b2Body &bodyA, b2Body &bodyB, int mass)
{
    b2Vec2 posA = bodyA.GetWorldCenter();
    b2Vec2 posB = bodyB.GetWorldCenter();
    b2Vec2 force = posA - posB;
    float distance = force.Length();
    force.Normalize();
    float strength = (gravity->y * bodyA.GetMass() * bodyA.GetGravityScale() * mass) / (distance * distance);
    force.operator*=(strength);
    return force;
}

void ObjectController::stepBox2DWorld()
{

    // Need this to avoid collision looping faults
    std::vector<GameObjects::GameObject*> toDestroy;
    GameObjects::GameObject *playerExplode = nullptr;
    GameObjects::GameObject *projectileExplode = nullptr;

    for(int i = 0; i < objectsOnScreen.size(); i++) {
        if(objectsOnScreen[i]->getTypeString() == "enemy" || objectsOnScreen[i]->getTypeString() == "target") {
            objectsOnScreen[i]->getBody()->ApplyLinearImpulseToCenter(
                                      attractBToA(*objectsOnScreen[i]->getBody(),
                                                  *player->getBody(), 1000), true);
        }
        else if (objectsOnScreen[i]->getTypeString() == "projectile") {
             GameObjects::Projectile *projectile = (GameObjects::Projectile *)(objectsOnScreen[i]);

             if(projectile->getTargetBody() != nullptr) {
                 b2Vec2 force = projectile->getTargetBody()->GetPosition() - projectile->getBody()->GetPosition();
                 force.operator*=(100);
                 projectile->getBody()->ApplyLinearImpulseToCenter(
                             force, true);
             }
             else if(projectile->getBody()->GetPosition().y < -windowSizeY){
                 toDestroy.push_back(projectile);
             }
             else {
                 projectile->getBody()->ApplyLinearImpulseToCenter(b2Vec2(0,-100), true);
             }
        }
    }

    // All body positions within world get updates after calling Step()
    world->Step(timeStep, velocityIterations, positionIterations);

    for(b2Contact *contact = world->GetContactList(); contact; contact = contact->GetNext()) {
        b2Body *bod1 = contact->GetFixtureA()->GetBody();
        b2Body *bod2 = contact->GetFixtureB()->GetBody();
        //    bod1     bod2
        // 1) enemy -- projectile
        // 2) enemy -- player
        // 3) projectile -- enemy
        // 4) player -- enemy

        if (static_cast<GameObjects::GameObject*> (bod1->GetUserData())->getTypeString() == "enemy"
                || static_cast<GameObjects::GameObject*> (bod1->GetUserData())->getTypeString() == "target") {
            if(static_cast<GameObjects::GameObject*>(bod2->GetUserData())->getTypeString() == "projectile") {
                GameObjects::Projectile *proj = static_cast<GameObjects::Projectile*>(bod2->GetUserData());
                // Explosion at enemy
                if(proj->getKillShot() && proj->getTargetBody() == bod1) {
                    qInfo() << "Killing enemy ";
                    projectileExplode = proj;
//                    createEnemyExplosion(proj);
                }
                else if(proj->getTargetBody() == bod1){
                    toDestroy.push_back(proj);
                }
            }
            if(static_cast<GameObjects::GameObject*>(bod2->GetUserData())->getTypeString() == "player") {
                // Explosion at player
                playerExplode = (static_cast<GameObjects::GameObject*> (bod1->GetUserData()));
//                createPlayerExplosion(static_cast<GameObjects::GameObject*> (bod1->GetUserData()));
            }
        }
        else if (static_cast<GameObjects::GameObject*> (bod1->GetUserData())->getTypeString() == "projectile") {
             GameObjects::Projectile *proj = static_cast<GameObjects::Projectile*>(bod1->GetUserData());
            if (static_cast<GameObjects::GameObject*> (bod2->GetUserData())->getTypeString() == "enemy"
                    || static_cast<GameObjects::GameObject*> (bod2->GetUserData())->getTypeString() == "target") {
                // Explosion at enemy
                if(proj->getKillShot() && proj->getTargetBody() == bod2) {
                     qInfo() << "Killing enemy ";
                     projectileExplode = proj;
//                    createEnemyExplosion(proj);
                }
                else if(proj->getTargetBody() == bod2) {
                    toDestroy.push_back(proj);
                }
            }
        }
        else if (static_cast<GameObjects::GameObject*> (bod1->GetUserData())->getTypeString() == "player") {
            if (static_cast<GameObjects::GameObject*> (bod2->GetUserData())->getTypeString() == "enemy"
                    || static_cast<GameObjects::GameObject*> (bod2->GetUserData())->getTypeString() == "target") {
                // Explosion at player
                playerExplode = (static_cast<GameObjects::GameObject*> (bod2->GetUserData()));
//                 createPlayerExplosion(static_cast<GameObjects::GameObject*> (bod2->GetUserData()));
            }
        }
    }

    for(int i = 0; i < toDestroy.size(); i++) {
        removeObjectAndDestroyBody(toDestroy[i]);
    }

    if(projectileExplode != nullptr) {
        qDebug() << "createEnemyExplosion";
        createEnemyExplosion(projectileExplode);
    }
    if(playerExplode != nullptr) {
        qDebug() << "createPlayerExplosion";
        createPlayerExplosion(playerExplode);
    }
}

GameObjects::Enemy *ObjectController::b2MakeNewEnemy(int round, std::string word)
{
    std::string imagePath = imagePaths.at(enemyImagePathIndex++);

    int boxSize = GameObjects::Enemy::getSize(word.size());
    b2BodyDef enemyBodyDef;
    enemyBodyDef.type = b2_dynamicBody;
    enemyBodyDef.position.Set((rand() % (int)windowSizeX), 0);

    b2Body *enemyBody = world->CreateBody(&enemyBodyDef);
    b2PolygonShape boxShape;
    boxShape.SetAsBox(boxSize/4, boxSize/4);

    b2FixtureDef boxFixtureDef;
    boxFixtureDef.shape = &boxShape;
    boxFixtureDef.density = 1;

    // Controls the speed of the enemy via proxy
    enemyBody->SetGravityScale(round * 0.2);

    enemyBody->CreateFixture(&boxFixtureDef);

    GameObjects::Enemy *enemy = new GameObjects::Enemy(round, word, imagePath, boxSize, {enemyBodyDef.position.x, windowSizeY}, *enemyBody);
    enemyBody->SetUserData(enemy);

    return enemy;
}

GameObjects::Player *ObjectController::b2MakeNewPlayer()
{
    b2BodyDef playerBodyDef;
    playerBodyDef.type = b2_staticBody;

    // Player position - 10% up from the bottom and in the middle of the screen
    playerBodyDef.position.Set((windowSizeX/2), -(0.9*windowSizeY));

    b2Body *playerBody = world->CreateBody(&playerBodyDef);
    b2PolygonShape boxShape;
    boxShape.SetAsBox(10, 10);

    b2FixtureDef boxFixtureDef;
    boxFixtureDef.shape = &boxShape;
    boxFixtureDef.density = 100000;

    playerBody->CreateFixture(&boxFixtureDef);

    GameObjects::Player *player = new GameObjects::Player({playerBodyDef.position.x, playerBodyDef.position.y}, *playerBody);

    playerBody->SetUserData(player);

    return player;
}

GameObjects::Projectile *ObjectController::b2MakeNewProjectile(b2Body *targetBody, bool killShot)
{
    b2BodyDef enemyBodyDef;
    enemyBodyDef.type = b2_dynamicBody;
    enemyBodyDef.bullet = true;
    enemyBodyDef.position.Set(std::get<0>(player->getPos())/4,-std::get<1>(player->getPos())/4);

    b2Body *projectileBody = world->CreateBody(&enemyBodyDef);
    b2PolygonShape boxShape;
    boxShape.SetAsBox(1,1);

    b2FixtureDef boxFixtureDef;
    boxFixtureDef.shape = &boxShape;
    boxFixtureDef.density = 1;
    boxFixtureDef.friction = 0;

    boxFixtureDef.isSensor = true;

    projectileBody->CreateFixture(&boxFixtureDef);

    projectileBody->SetBullet(true);
    GameObjects::Projectile *projectile = new GameObjects::Projectile({enemyBodyDef.position.x, enemyBodyDef.position.y},
                                                                          *projectileBody, targetBody, killShot);
    projectileBody->SetUserData(projectile);
    projectileBody->SetActive(true);

    projectileBody->SetGravityScale(1);

    return projectile;
}
