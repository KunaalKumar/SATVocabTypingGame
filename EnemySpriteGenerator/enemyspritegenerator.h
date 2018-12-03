#ifndef ENEMYSPRITEGENERATOR_H
#define ENEMYSPRITEGENERATOR_H

#include "shipstructures.h"

class EnemySpriteGenerator
{
public:
    EnemySpriteGenerator();
    QImage generateNewEnemy(ShipSize ss);
private:
    std::vector<ShipStructure> structures;
    void setRegionColors();
};

#endif // ENEMYSPRITEGENERATOR_H
