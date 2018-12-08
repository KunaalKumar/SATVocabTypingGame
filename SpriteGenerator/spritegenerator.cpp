#include "spritegenerator.h"
#include <QFile>
#include <QDirIterator>
#include <QTextStream>
#include <QException>

SpriteGenerator::SpriteGenerator() {}

SpriteGenerator::SpriteGenerator(QString folderPath)
    : structureFolderPath(folderPath)
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
    case SpriteSize::modular:
        shipStructure = getModularSprite();
        break;

    default:
        throw "Sprite size given to generateNewSprite was invalid!";
    }

    return setAllRegionColors(shipStructure);
}

QImage SpriteGenerator::setAllRegionColors(SpriteStructure shipStructure)
{
    shipStructure.image.fill(Qt::transparent);
    for (auto regionIter = shipStructure.regions.begin(); regionIter != shipStructure.regions.end(); regionIter++)
    {
        int red = rand() % 255;
        int blue = rand() % 255;
        int green = rand() % 255;
        QColor color(red, blue, green);

        setRegionColor(regionIter->second, shipStructure, color);
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

SpriteStructure SpriteGenerator::getModularSprite()
{
    SpriteStructure spriteTop;
    SpriteStructure spriteMiddle;
    SpriteStructure spriteBottom;

    bool evenOrOdd = rand() % 2;

    if (evenOrOdd)
    {
        spriteTop    = modularTopEven[rand() % modularTopEven.size()];
        spriteMiddle = modularMiddleEven[rand() % modularMiddleEven.size()];
        spriteBottom = modularBottomEven[rand() % modularBottomEven.size()];
    }
    else
    {
        spriteTop    = modularTopOdd[rand() % modularTopOdd.size()];
        spriteMiddle = modularMiddleOdd[rand() % modularMiddleOdd.size()];
        spriteBottom = modularBottomOdd[rand() % modularBottomOdd.size()];
    }

    return constructModularSprite(evenOrOdd, spriteTop, spriteMiddle, spriteBottom);
}

SpriteStructure SpriteGenerator::constructModularSprite(bool evenOrOdd, SpriteStructure top, SpriteStructure middle, SpriteStructure bottom)
{
    std::map<QString, CoordinateList> regions;
    for (auto topIter = top.regions.begin(); topIter != top.regions.end(); topIter++)
    {
        for (Coordinate c : topIter->second)
        {
            regions[topIter->first].push_back(c);
        }
    }

    for (auto middleIter = middle.regions.begin(); middleIter != middle.regions.end(); middleIter++)
    {
        for (Coordinate c : middleIter->second)
        {
            evenOrOdd ? c.oddOffsetMiddle() : c.oddOffsetMiddle();
            regions[middleIter->first].push_back(c);
        }
    }

    for (auto bottomIter = bottom.regions.begin(); bottomIter != bottom.regions.end(); bottomIter++)
    {
        for (Coordinate c : bottomIter->second)
        {
            evenOrOdd ? c.evenOffsetBottom() : c.oddOffsetBottom();
            regions[bottomIter->first].push_back(c);
        }
    }

    return SpriteStructure(top.size, top.size * 3, regions);
}

void SpriteGenerator::getAllSpriteStructures()
{
    smallSprites = getSpriteStructuresFromFolder(structureFolderPath + smallSpritesFolder);
    mediumSprites = getSpriteStructuresFromFolder(structureFolderPath + mediumSpritesFolder);
    largeSprites = getSpriteStructuresFromFolder(structureFolderPath + largeSpritesFolder);
    veryLargeSprites = getSpriteStructuresFromFolder(structureFolderPath + veryLargeSpritesFolder);

    modularTopOdd = getSpriteStructuresFromFolder(structureFolderPath + modularTopOddFolder);
    modularMiddleOdd = getSpriteStructuresFromFolder(structureFolderPath + modularMiddleOddFolder);
    modularBottomOdd = getSpriteStructuresFromFolder(structureFolderPath + modularBottomOddFolder);

    modularTopEven = getSpriteStructuresFromFolder(structureFolderPath + modularTopEvenFolder);
    modularMiddleEven = getSpriteStructuresFromFolder(structureFolderPath + modularMiddleEvenFolder);
    modularBottomEven = getSpriteStructuresFromFolder(structureFolderPath + modularBottomEvenFolder);
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
    std::map<QString, CoordinateList> regions;

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
        regions[colorString] = region;
    }
    return SpriteStructure(imageSize, imageSize, regions);
}

