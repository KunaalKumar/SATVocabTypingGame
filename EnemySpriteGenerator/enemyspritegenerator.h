#ifndef ENEMYSPRITEGENERATOR_H
#define ENEMYSPRITEGENERATOR_H

#include "shipstructures.h"

class EnemySpriteGenerator
{
public:
    EnemySpriteGenerator();
    QImage generateNewEnemy(ShipSize ss);
private:
    std::vector<ShipStructure> smallShips;
    std::vector<ShipStructure> mediumShips;
    std::vector<ShipStructure> largeShips;
    std::vector<ShipStructure> hugeShips;
    QImage setRegionColors(ShipStructure);
};

#endif // ENEMYSPRITEGENERATOR_H
