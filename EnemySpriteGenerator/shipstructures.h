#ifndef SHIPSTRUCTURES_H
#define SHIPSTRUCTURES_H

#include <QImage>
#include <vector>
#include <tuple>

using CooordinateList = std::vector<std::tuple<int>>;

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
std::vector<ShipStructure> generateStructures()
{
    std::vector<ShipStructure> structures;

    structures.push_back(createSmallShip1());
    //...

    return structures;
}

#endif // SHIPSTRUCTURES_H
