#ifndef ENEMYSPRITEGENERATOR_H
#define ENEMYSPRITEGENERATOR_H

#include "shipstructures.h"

class EnemySpriteGenerator
{
public:
    EnemySpriteGenerator();
    QImage generateNewEnemy(ShipSize ss);
private:
    std::vector<ShipStrucutre> structures;
    void setRegionColors();
};

#endif // ENEMYSPRITEGENERATOR_H
