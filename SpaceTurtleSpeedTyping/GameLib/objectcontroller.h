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

    void createPlayer();
    void createRoundOfEnemies(int round);
    void createEnemy(int round);
    void createExplosion();
    // call after letterTyped
    void createProjectile();

    using hitEnemy = bool;
    hitEnemy letterTyped(char letter);

    const std::vector<GameObjects::GameObject *>& getObjects();

<<<<<<< HEAD
    // Updates all object positions in objectsOnScreen
    void updateObjectPositions();
=======
    // Updates all object positions in currentEnemeies
    void updateObjectPositions();

>>>>>>> 365a03a7a7f37cbe35f054225bc0acf203d2fddd
    bool isEnemyKilled();
    bool isRoundEnd();
    bool isEndGame();

 private:
<<<<<<< HEAD
    // shoot closest enemy with starting letter = letter
    void findNewTargetedEnemy(char letter);

    GameObjects::Player *player;
    GameObjects::TargetedEnemy *targetedEnemy;
    GameObjects::Explosion *explosion;
    std::vector<GameObjects::GameObject*> objectsOnScreen;
=======
    GameObjects::Player player;
    GameObjects::TargetedEnemy *targetedEnemy;
    std::vector<GameObjects::Enemy> currentEnemies;
    std::vector<GameObjects::Projectile> projectiles;
>>>>>>> 365a03a7a7f37cbe35f054225bc0acf203d2fddd

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
<<<<<<< HEAD

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
=======
>>>>>>> 365a03a7a7f37cbe35f054225bc0acf203d2fddd
};

#endif // OBJECTCONTROLLER_H
