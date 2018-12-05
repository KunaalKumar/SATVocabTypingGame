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

using CoordinateList = std::vector<Cooridante>;

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
    std::vector<CoordinateList> regions;
    ShipSize size;
};

ShipStructure createShip(ShipSize ss, std::vector<CoordinateList> regions)
{
    ShipStructure structure;
    structure.size = ss;
    structure.image = QImage(ss, ss, QImage::Format_ARGB32);
    structure.regions = regions;

    return structure;
}

#endif // SHIPSTRUCTURES_H
