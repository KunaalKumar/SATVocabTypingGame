#ifndef SHIPSTRUCTURES_H
#define SHIPSTRUCTURES_H

#include <QImage>
#include <vector>
#include <tuple>

struct Cooridante
{
    int x;
    int y;
    Cooridante(int x,int y)
    {
        this->x = x;
        this->y = y;
    }
};

Cooridante makeCoordinate(int x, int y)
{
    return Cooridante(x,y);
}

using CooordinateList = std::vector<Cooridante>;

enum ShipSize
{
    small = 8,
    medium = 16,
    large = 32,
    huge = 64
};

struct ShipStructure
{
    QImage image;
    std::vector<CooordinateList> regions;
    ShipSize size;
};

ShipStructure createShip(ShipSize ss, std::vector<CooordinateList> regions)
{
    ShipStructure structure;
    structure.size = ss;
    structure.image = QImage(ss, ss, QImage::Format_ARGB32);
    structure.regions = regions;

    return structure;
}

ShipStructure createSmallShip1()
{
    //create regions here
    std::vector<CooordinateList> regions;

    return createShip(ShipSize::small, regions);
}

//Define structures here
std::vector<ShipStructure> generateSmallShips()
{
    std::vector<ShipStructure> structures;

    structures.push_back(createSmallShip1());
    //...

    return structures;
}

std::vector<ShipStructure> generateMediumShips()
{
    std::vector<ShipStructure> structures;

    //structures.push_back(createMediumShip1);
    //...

    return structures;
}

std::vector<ShipStructure> generateLargeShips()
{
    std::vector<ShipStructure> structures;

    //structures.push_back(createLargeShip1);
    //...

    return structures;
}

std::vector<ShipStructure> generateHugeShips()
{
    std::vector<ShipStructure> structures;

    //structures.push_back(createHugeShip1);
    //...

    return structures;
}

#endif // SHIPSTRUCTURES_H
