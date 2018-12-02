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

    bool isEnemyKilled();
    bool isRoundEnd();
    bool isEndGame();

 private:
    GameObjects::Player player;
    GameObjects::TargetedEnemy *targetedEnemy;
    std::vector<GameObjects::Enemy> currentEnemies;
    std::vector<GameObjects::Projectile> projectiles;
    b2World *world;

    int frameCounter;
    bool stopCreatingEnemies;
};

#endif // OBJECTCONTROLLER_H
