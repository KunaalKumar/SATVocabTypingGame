#ifndef SHIPSTRUCTURES_H
#define SHIPSTRUCTURES_H

#include <QImage>
#include <vector>
#include <tuple>

struct Coordinate
{
    int x;
    int y;
    Coordinate(int x,int y)
    {
        this->x = x;
        this->y = y;
    }
    Coordinate(QString commaPair)
    {
        QStringList list = commaPair.split(',');
        QString xString = list.at(0);
        QString yString = list.at(1);

        this->x = xString.toInt();
        this->y = yString.toInt();
    }
    void oddOffsetMiddle() { y += 8; }
    void evenOffsetMiddle() { y += 7; }
    void oddOffsetBottom() { y += 16; }
    void evenOffsetBottom() { y += 14; }
};

using CoordinateList = std::vector<Coordinate>;

enum SpriteSize
{
    small = 16,
    medium = 24,
    large = 48,
    veryLarge = 64,
    modular = -1
};

struct SpriteStructure
{
    QImage image;
    std::map<QString, CoordinateList> regions;
    int size;

    SpriteStructure() {};
    \
    SpriteStructure(int sizeX, int sizeY, std::map<QString, CoordinateList> regions)
    {
        this->size = sizeX;
        image = QImage(sizeX, sizeY, QImage::Format_ARGB32);
        this->regions = regions;
    }
};

#endif // SHIPSTRUCTURES_H
