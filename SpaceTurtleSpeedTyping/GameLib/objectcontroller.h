#ifndef OBJECTCONTROLLER_H
#define OBJECTCONTROLLER_H

#include "enemy.h"
#include "gameobjects.h"
#include "player.h"
#include "projectile.h"
#include "loadwords.h"
#include <Box2D/Box2D.h>

#include <string>
#include <float.h>
#include <vector>

class ObjectController
{
public:
    ObjectController();
    ~ObjectController();

    GameObjects::Player createPlayer();
    void createRoundOfEnemies(int round);
    GameObjects::Enemy createEnemy(int round);

    // call after letterTyped
    GameObjects::Projectile createProjectile();
    using hitEnemy = bool;
    hitEnemy letterTyped(char letter);

    // to be called when isEnemyKilled == true and next letterTyped == true
    GameObjects::TargetedEnemy getTargetedEnemy();

    // Updates all object positions in currentEnemeies
    void updateObjectPositions();

    bool isEnemyKilled();
    bool isRoundEnd();
    bool isEndGame();

 private:
    GameObjects::Player player;
    GameObjects::TargetedEnemy *targetedEnemy;
    std::vector<GameObjects::GameObject> objectsOnScreen;

    int frameCounter;
    bool stopCreatingEnemies;

    // Box2D instances
    b2World *world;
    // Enemy Body Definition
    b2BodyDef enemyBodyDef;
    // TODO: Sync timeStep with front end update rate
    float32 timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 8;
    int32 positionIterations = 3;
};

#endif // OBJECTCONTROLLER_H
