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

class ObjectController
{
public:
    ObjectController();
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
    void createPlayer();
    void createEnemy(int round);
    void createProjectile();
    void createExplosion();

    // shoot closest enemy with starting letter = letter
    void findNewTargetedEnemy(char letter);

    GameObjects::Player *player;
    GameObjects::TargetedEnemy *targetedEnemy;
    GameObjects::Explosion *explosion;
    std::vector<GameObjects::GameObject*> objectsOnScreen;

    int frameCounter;
    bool stopCreatingEnemies;

    // Box2D instances
    b2World *world;
    // Enemy Body Definition
    b2BodyDef enemyBodyDef;
    // Player Body Definition
    b2BodyDef playerBodyDef;
    // TODO: Sync timeStep with front end update rate
    float32 timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 8;
    int32 positionIterations = 3;

    /**
     * @brief attractAToB - attracts body B to body A
     * @param bodyA
     * @param bodyB
     */
    void attractAToB(b2Body &bodyA, b2Body &bodyB);

    /**
     * @brief stepBox2DWorld - increments box2d world and checks for collisions
     */
    void stepBox2DWorld();

    /**
     * @brief initBox2DWorld - initializes b2World and fixtures
     */
    void initBox2DWorld();

    /**
     * @brief b2MakeNewEnemy - Adds new enemy body into b2World and returns a pointer to it
     * @param round - number of current round
     * @return
     */
    GameObjects::Enemy *b2MakeNewEnemy(int round);

    /**
     * @brief b2MakeNewPlayer - Adds new player body into b2World and returns a pointer to it
     * @return
     */
    GameObjects::Player *b2MakeNewPlayer();
};

#endif // OBJECTCONTROLLER_H
