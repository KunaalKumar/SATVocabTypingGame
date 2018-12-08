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

void ObjectController::createPlayer()
{
    player = b2MakeNewPlayer();
    objectsOnScreen.push_back(player);
}

void ObjectController::createRoundOfEnemies(int round)
{
    this->round = round;
    createImagePaths();
    LoadWords::createRoundWords(round);
    stopCreatingEnemies = false;
}

void ObjectController::createEnemy()
{
    std::string word = LoadWords::getWord();
    if (word != "")
    {
        GameObjects::Enemy *enemy = b2MakeNewEnemy(this->round, word);
        objectsOnScreen.push_back(enemy);
    }
    else
    {
        stopCreatingEnemies = true;
    }
}

void ObjectController::createProjectile(bool hitEnemy)
{
    if (!hitEnemy)
    {
        objectsOnScreen.push_back(b2MakeNewProjectile(nullptr, false));
    }
    else
    {
        if (targetedEnemy->wasDestroyed())
        {
            objectsOnScreen.push_back(b2MakeNewProjectile(&targetedEnemy->getBody(), true));
            enemyExplosion = new GameObjects::Explosion(targetedEnemy->getPos());

            //delete targetedEnemy;
            targetedEnemy = nullptr;
        }
        else
        {
            objectsOnScreen.push_back(b2MakeNewProjectile(&targetedEnemy->getBody(), false));

        }
    }
}

void ObjectController::findNewTargetedEnemy(char letter)
{
    double lowestDistance = DBL_MAX;
    int index = 0;
    GameObjects::TargetedEnemy *tempTarget = nullptr;
    for (unsigned int i = 0; i < objectsOnScreen.size(); i++)
    {
        if (objectsOnScreen[i]->isOfType(GameObjects::Type::enemy))
        {
            GameObjects::Enemy enemy = *(static_cast<GameObjects::Enemy *>(objectsOnScreen[i]));
            double distance;

            if (enemy.startsWith(letter) && (distance = enemy.distanceTo(player->getPos())) < lowestDistance)
            {
                tempTarget = new GameObjects::TargetedEnemy(enemy);
                index = i;
            }
        }
    }

    if (tempTarget != nullptr)
    {
        targetedEnemy = tempTarget;
        objectsOnScreen[index] = targetedEnemy;
    }
}

bool ObjectController::letterTyped(char letter)
{
    bool noTargetedEnemy = targetedEnemy == nullptr;
    if (noTargetedEnemy)
    {
        findNewTargetedEnemy(letter);

        bool hit = false;
        bool foundTargetEnemy = targetedEnemy != nullptr;
        if (foundTargetEnemy)
        {
            hit = targetedEnemy->shoot(letter);
            if (!hit)
            {
                targetedEnemy->resetWord();
            }
        }

        createProjectile(hit);
        return targetedEnemy == nullptr;
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

void ObjectController::createPlayerExplosion(GameObjects::GameObject *enemyObject)
{
    for(int i = 0 ; i < objectsOnScreen.size(); i++) {
        if(objectsOnScreen[i] == enemyObject) {
            world->DestroyBody(&objectsOnScreen[i]->getBody());
            objectsOnScreen.erase(objectsOnScreen.begin() + i);
            break;
        }
    }

    playerExplosion = new GameObjects::Explosion(player->getPos());
    objectsOnScreen.push_back(playerExplosion);
}

void ObjectController::removePlayerExplosion()
{
    int index = findIndexOfType(GameObjects::Type::explosion, playerExplosion);
    delete objectsOnScreen[index];
    objectsOnScreen.erase(objectsOnScreen.begin() + index);
    delete playerExplosion;
    playerExplosion = nullptr;
}

void ObjectController::createEnemyExplosion(GameObjects::Projectile *projectileObject)
{
    int index = findIndexOfType(GameObjects::Type::targetedEnemy);
    delete objectsOnScreen[index];
    objectsOnScreen[index] = enemyExplosion;

    index = findIndexOfType(GameObjects::Type::projectile, projectileObject);
    delete objectsOnScreen[index];
    objectsOnScreen.erase(objectsOnScreen.begin() + index);

}

void ObjectController::removeEnemyExplosion()
{
    unsigned int index = findIndexOfType(GameObjects::Type::explosion, enemyExplosion);
    delete objectsOnScreen[index];
    objectsOnScreen.erase(objectsOnScreen.begin() + index);

    delete enemyExplosion;
    enemyExplosion = nullptr;
}

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
    if (enemyExplosion != nullptr && enemyExplosion->getNumOfFrames() == 100)
    {
        removeEnemyExplosion();
    }

    // End of playerExplosion Timer
    if (playerExplosion != nullptr && playerExplosion->getNumOfFrames() == 500)
    {
        removePlayerExplosion();
    }
}

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
        if(objectsOnScreen[i]->getTypeString() == "enemy" || objectsOnScreen[i]->getTypeString() == "target") {
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
        b2Body *bod1 = contact->GetFixtureA()->GetBody();
        b2Body *bod2 = contact->GetFixtureB()->GetBody();
        //    bod1     bod2
        // 1) enemy -- projectile
        // 2) enemy -- player
        // 3) projectile -- enemy
        // 4) player -- enemy

        if (static_cast<GameObjects::GameObject*> (bod1->GetUserData())->getTypeString() == "enemy") {
            if(static_cast<GameObjects::GameObject*>(bod2->GetUserData())->getTypeString() == "projectile") {
                // Explosion at enemy
                if(static_cast<GameObjects::Projectile*>(bod2->GetUserData())->getKillShot()) {
                    createEnemyExplosion(static_cast<GameObjects::Projectile*>(bod2->GetUserData()));
                }
            }
            if(static_cast<GameObjects::GameObject*>(bod2->GetUserData())->getTypeString() == "player") {
                // Explosion at player
                createPlayerExplosion(static_cast<GameObjects::GameObject*> (bod1->GetUserData()));
            }
        }
        else if (static_cast<GameObjects::GameObject*> (bod1->GetUserData())->getTypeString() == "projectile") {
                // Explosion at enemy
                if(static_cast<GameObjects::Projectile*>(bod1->GetUserData())->getKillShot()) {
                    createEnemyExplosion(static_cast<GameObjects::Projectile*>(bod1->GetUserData()));
                }
        }
        else if (static_cast<GameObjects::GameObject*> (bod1->GetUserData())->getTypeString() == "player") {
//                 world->DestroyBody(bod1);
                // Explosion at player
                 createPlayerExplosion(static_cast<GameObjects::GameObject*> (bod2->GetUserData()));
        }
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

GameObjects::Projectile *ObjectController::b2MakeNewProjectile(b2Body *targetBody, bool killShot)
{
    playerBodyDef.position.Set(std::get<0>(player->getPos()),std::get<1>(player->getPos()));

    b2Body *projectileBody = world->CreateBody(&playerBodyDef);
    b2PolygonShape boxShape;
    boxShape.SetAsBox(1,1);

    b2FixtureDef boxFixtureDef;
    boxFixtureDef.shape = &boxShape;
    boxFixtureDef.density = 1;

    GameObjects::Projectile *projectile;

    projectile = new GameObjects::Projectile({playerBodyDef.position.x, playerBodyDef.position.y},
                                                                          *projectileBody, targetBody, killShot);
    projectileBody->SetUserData(projectile);

    projectileBody->SetGravityScale(100);

    return projectile;
}
