#ifndef OBJECTCONTROLLER_H
#define OBJECTCONTROLLER_H

#include "enemy.h"
#include "gameobjects.h"

#include <string>
#include <float.h>
#include <vector>

class ObjectController
{
public:
    ObjectController();
    void createRoundOfEnemies();
    void createEnemy();
    bool shoot(char letter);

 private:
    int round;
    GameObjects::Enemy *currentEnemy;
    std::vector<GameObjects::Enemy> currentEnemies;
};

#endif // OBJECTCONTROLLER_H
