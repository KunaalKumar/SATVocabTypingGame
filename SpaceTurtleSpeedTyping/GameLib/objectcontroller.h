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
    void createRoundOfEnemies(int round);
    void createEnemy(int round);
    bool shoot(char letter);

 private:
    GameObjects::Enemy *currentEnemy;
    std::vector<GameObjects::Enemy> currentEnemies;
};

#endif // OBJECTCONTROLLER_H
