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
};

using CoordinateList = std::vector<Coordinate>;

enum SpriteSize
{
    small = 8,
    medium = 16,
    large = 32,
    veryLarge = 64
};

struct SpriteStructure
{
    QImage image;
    std::vector<CoordinateList> regions;
    SpriteSize size;

    SpriteStructure() {};
    \
    SpriteStructure(SpriteSize ss, std::vector<CoordinateList> regionVec)
    {
        image= QImage(ss, ss, QImage::Format_ARGB32);
        size = ss;
        regions = regionVec;
    }
};

#endif // SHIPSTRUCTURES_H
