#ifndef OBJECTCONTROLLER_H
#define OBJECTCONTROLLER_H

#include "enemy.h"
#include "gameobjects.h"
#include "player.h"
#include "projectile.h"
#include "loadwords.h"
#include "explosion.h"

#include <Box2D/Box2D.h>

#include <string>
#include <float.h>
#include <vector>
#include <QDebug>

class ObjectController
{
public:
    ObjectController(int windowSizeX, int windowSizeY);
    ~ObjectController();

    void createRoundOfEnemies(int round);

    using hitEnemy = bool;
    hitEnemy letterTyped(char letter);

    const std::vector<GameObjects::GameObject *>& getObjects();

    // Updates all object positions in objectsOnScreen
    void updateObjectPositions();
    bool isEnemyKilled();
    bool isRoundEnd();
    bool isEndGame();

 private:
    int windowSizeX;
    int windowSizeY;
    int round;

    void createPlayer();
    void createEnemy();
    void createProjectile(bool hitEnemy);
    void createPlayerExplosion(GameObjects::GameObject *enemyObject);
    void createEnemyExplosion(GameObjects::Projectile *projectileObject);

    // shoot closest enemy with starting letter = letter
    void findNewTargetedEnemy(char letter);

    void removeEnemyExplosion();
    void removePlayerExplosion();

    int findIndexOfType(GameObjects::Type type, GameObjects::GameObject *gameObject = nullptr);
    void removeOldEnemyExplosion();
    void removeOldPlayerExplosion();
    void removeObjectAndDestroyBody(GameObjects::GameObject*obj);

    GameObjects::Player *player;
    GameObjects::TargetedEnemy *targetedEnemy;
    GameObjects::Explosion *enemyExplosion;
    GameObjects::Explosion *playerExplosion;
    std::vector<GameObjects::GameObject*> objectsOnScreen;

    int frameCounter;
    bool stopCreatingEnemies;

    // SG Stuff
    void initSpriteGenerator();
    void createImagePaths();

    SpriteGenerator sg;
    std::vector<std::string> imagePaths;
    unsigned int imageCounter;
    unsigned int enemyImagePathIndex;


    // Box2D instances
    b2World *world;
    // World gravity
    b2Vec2 *gravity;
    // TODO: Sync timeStep with front end update rate
    // Frontend - 17 ms
    // Backend  - 1/60 - 16.6 ms
    float32 timeStep = 1.0f/60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 3;

    /**
     * @brief stepBox2DWorld - increments box2d world and checks for collisions
     */
    void stepBox2DWorld();

    /**
     * @brief initBox2DWorld - initializes b2World and fixtures
     */
    void initBox2DWorld();

    /**
     * @brief attractBToA - attracts body B to body Agigggg
     * @param bodyA
     * @param bodyB
     * @return - vector to apply
     */
    b2Vec2 attractBToA(b2Body &bodyA, b2Body &bodyB, int mass);

    /**
     * @brief b2MakeNewEnemy - Adds new enemy body into b2World and returns a pointer to it
     * @param round - number of current round
     * @return
     */
    GameObjects::Enemy *b2MakeNewEnemy(int round, std::string word);

    /**
     * @brief b2MakeNewPlayer - Adds new player body into b2World and returns a pointer to it
     * @return
     */
    GameObjects::Player *b2MakeNewPlayer();

    /**
     * @brief b2MakeNewProjectile - Adds new projectile body into b2World
     * @param targetBody - target to hit
     * @return - projectile object
     */
    GameObjects::Projectile *b2MakeNewProjectile(GameObjects::TargetedEnemy *targetedEnemy, b2Body *targetBody, bool killShot);

    class MyContactListener : public b2ContactListener
    {
    public:
     void BeginContact(b2Contact* contact)
     {
         qInfo() << "Something";
         /* handle begin event */ }
     void EndContact(b2Contact* contact)
     { /* handle end event */ qInfo() << "Something";}
     void PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
     { /* handle pre-solve event */ qInfo() << "Something";}
     void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
     { /* handle post-solve event */ qInfo() << "Something";}
    };

};

#endif // OBJECTCONTROLLER_H
