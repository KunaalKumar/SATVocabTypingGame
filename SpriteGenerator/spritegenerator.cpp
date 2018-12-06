#include "spritegenerator.h"
#include <QFile>
#include <QDirIterator>
#include <QTextStream>
#include <QException>


SpriteGenerator::SpriteGenerator()
{
    SpriteGenerator("SpriteStructures/");
}

SpriteGenerator::SpriteGenerator(QString folderPath, QString ssFolder, QString msFolder, QString lsFolder, QString vlsFolder)
    : structureFolderPath(folderPath),
      smallSpritesFolder(ssFolder),
      mediumSpritesFolder(msFolder),
      largeSpritesFolder(lsFolder),
      veryLargeSpritesFolder(vlsFolder)
{
    getAllSpriteStructures();
}

QImage SpriteGenerator::generatreNewSprite(SpriteSize ss)
{
    SpriteStructure shipStructure;
    switch (ss)
    {
    case SpriteSize::small:
        if (smallSprites.size() > 0)
        {
            shipStructure = smallSprites[rand() % smallSprites.size()];
        }
        else {throw "No small sprite structures exist!";}
        break;

    case SpriteSize::medium:
        if (mediumSprites.size() > 0)
        {
            shipStructure = mediumSprites[rand() % mediumSprites.size()];
        }
        else {throw "No medium sprite structures exist!";}
        break;

    case SpriteSize::large:
        if (largeSprites.size() > 0)
        {
            shipStructure = largeSprites[rand() % largeSprites.size()];
        }
        else {throw "No large sprite strucutres exist!";}
        break;

    case SpriteSize::veryLarge:
        if (veryLargeSprites.size() > 0)
        {
            shipStructure = veryLargeSprites[rand() % veryLargeSprites.size()];
        }
        else {throw "No very large sprite strucutres exists!";}
        break;

    default:
        throw "Sprite size given to generateNewSprite was invalid!";
    }

    return setAllRegionColors(shipStructure);
}

QImage SpriteGenerator::setAllRegionColors(SpriteStructure shipStructure)
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

void SpriteGenerator::setRegionColor(CoordinateList region, SpriteStructure& ss, QColor color)
{
    for (Coordinate coordinate : region)
    {
        ss.image.setPixelColor(coordinate.x, coordinate.y, color);
    }

}

void SpriteGenerator::getAllSpriteStructures()
{
    smallSprites = getSpriteStructuresFromFolder(structureFolderPath + smallSpritesFolder);
    mediumSprites = getSpriteStructuresFromFolder(structureFolderPath + mediumSpritesFolder);
    largeSprites = getSpriteStructuresFromFolder(structureFolderPath + largeSpritesFolder);
    veryLargeSprites = getSpriteStructuresFromFolder(structureFolderPath + veryLargeSpritesFolder);
}

std::vector<SpriteStructure> SpriteGenerator::getSpriteStructuresFromFolder(QString folderPath)
{
    std::vector<SpriteStructure> structures;

    QDirIterator dirIter(folderPath);
    while(dirIter.hasNext())
    {
        QString nextFilePath = dirIter.next();
        if (nextFilePath.contains(".qis"))
        {
            structures.push_back(getSpriteStructureFromFile(nextFilePath));
        }
    }

    return structures;
}

SpriteStructure SpriteGenerator::getSpriteStructureFromFile(QString filePath)
{
    std::vector<CoordinateList> regions;

    QFile loadFile(filePath);
    loadFile.open((QIODevice::ReadOnly | QIODevice::Text));
    QTextStream reader(&loadFile);

    int imageSize;
    reader >> imageSize;

    int regionsCount;
    reader >> regionsCount;
    for (int i = 0; i < regionsCount; i++)
    {
        int pixelsInRegion;
        reader >> pixelsInRegion;
        QString colorString;
        reader >> colorString;

        CoordinateList region;
        for (int j = 0; j < pixelsInRegion; j++)
        {
            QString coordPair;
            reader >> coordPair;
            Coordinate c(coordPair);
            region.push_back(c);
        }
        regions.push_back(region);
    }
    return SpriteStructure(static_cast<SpriteSize>(imageSize), regions);
}

