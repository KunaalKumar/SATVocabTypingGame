#ifndef ENEMYSPRITEGENERATOR_H
#define ENEMYSPRITEGENERATOR_H

#include "shipstructures.h"

class SpriteGenerator
{
public:
    SpriteGenerator();
    QImage generatreNewSprite(ShipSize ss);
private:
    std::vector<ShipStructure> smallShips;
    std::vector<ShipStructure> mediumShips;
    std::vector<ShipStructure> largeShips;
    std::vector<ShipStructure> hugeShips;
    QImage setAllRegionColors(ShipStructure);
    void setRegionColor(CoordinateList region, ShipStructure& ss, QColor color);
    void getSpriteStructures();
};

#endif // ENEMYSPRITEGENERATOR_H
