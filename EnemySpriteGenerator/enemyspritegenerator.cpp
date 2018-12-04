#include "enemyspritegenerator.h"


EnemySpriteGenerator::EnemySpriteGenerator()
{
    smallShips = generateSmallShips();
    mediumShips = generateMediumShips();
    largeShips = generateLargeShips();
    hugeShips = generateHugeShips();
}

QImage EnemySpriteGenerator::generateNewEnemy(ShipSize ss)
{
    ShipStructure shipStructure;
    switch (ss)
    {
    case ShipSize::small:
        shipStructure = smallShips[rand() % smallShips.size() - 1];
        break;
    case ShipSize::medium:
        shipStructure = mediumShips[rand() % mediumShips.size() - 1];
        break;
    case ShipSize::large:
        shipStructure = largeShips[rand() % largeShips.size() - 1];
        break;
    case ShipSize::huge:
        shipStructure = hugeShips[rand() % hugeShips.size() - 1];
        break;
    }

    return setRegionColors(shipStructure);
}


QImage EnemySpriteGenerator::setRegionColors(ShipStructure shipStructure)
{
    //
}
