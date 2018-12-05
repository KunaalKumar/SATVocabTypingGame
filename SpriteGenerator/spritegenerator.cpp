#include "spritegenerator.h"
#include <QFile>
#include <QDirIterator>
#include <QTextStream>


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
        shipStructure = smallSprites[rand() % smallSprites.size()];
        break;
    case SpriteSize::medium:
        shipStructure = mediumSprites[rand() % mediumSprites.size()];
        break;
    case SpriteSize::large:
        shipStructure = largeSprites[rand() % largeSprites.size()];
        break;
    case SpriteSize::veryLarge:
        shipStructure = veryLargeSprites[rand() % veryLargeSprites.size()];
        break;
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
        structures.push_back(getSpriteStructureFromFile(nextFilePath));
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

