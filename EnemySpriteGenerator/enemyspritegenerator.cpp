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
        shipStructure = smallShips[rand() % smallShips.size()];
        break;
    case ShipSize::medium:
        shipStructure = mediumShips[rand() % mediumShips.size()];
        break;
    case ShipSize::large:
        shipStructure = largeShips[rand() % largeShips.size()];
        break;
    case ShipSize::huge:
        shipStructure = hugeShips[rand() % hugeShips.size()];
        break;
    }

    return setAllRegionColors(shipStructure);
}


QImage EnemySpriteGenerator::setAllRegionColors(ShipStructure shipStructure)
{
    for (CoordinateList region : shipStructure.regions)
    {
        int red = rand() % 255;
        int blue = rand() % 255;
        int green = rand() % 255;
        QColor color(red, blue, green);

        setRegionColor(region, shipStructure, color);
    }

    return shipStructure.image;
}

void EnemySpriteGenerator::setRegionColor(CoordinateList region, ShipStructure& ss, QColor color)
{
    for (Cooridante coordinate : region)
    {
        ss.image.setPixelColor(coordinate.x, coordinate.y, color);
    }

}
