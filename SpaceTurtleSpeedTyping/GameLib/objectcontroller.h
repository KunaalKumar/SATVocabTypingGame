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

    GameObjects::Player createPlayer();

    void createRoundOfEnemies(int round);
    void createEnemy(int round);

    using hitEnemy = bool;
    hitEnemy letterTyped(char letter);
    GameObjects::Projectile createProjectile(); // call after shooting word

    bool isEnemyKilled();
    bool isRoundEnd();
    bool isEndGame();

 private:
    GameObjects::Player player;
    GameObjects::Enemy *targetedEnemy;
    std::vector<GameObjects::Enemy> currentEnemies;
    std::vector<GameObjects::Projectile> projectiles;
    b2World *world;

    int frameCounter;
};

#endif // OBJECTCONTROLLER_H
