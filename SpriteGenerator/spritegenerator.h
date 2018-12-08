#ifndef ENEMYSPRITEGENERATOR_H
#define ENEMYSPRITEGENERATOR_H

#include "spritestructures.h"
#include <QDir>


class SpriteGenerator
{
public:
    SpriteGenerator();
    SpriteGenerator(QString filepath);

    QImage generatreNewSprite(SpriteSize ss);

private:
    std::vector<SpriteStructure> smallSprites;
    std::vector<SpriteStructure> mediumSprites;
    std::vector<SpriteStructure> largeSprites;
    std::vector<SpriteStructure> veryLargeSprites;
    std::vector<SpriteStructure> modularTopOdd;
    std::vector<SpriteStructure> modularMiddleOdd;
    std::vector<SpriteStructure> modularBottomOdd;
    std::vector<SpriteStructure> modularTopEven;
    std::vector<SpriteStructure> modularMiddleEven;
    std::vector<SpriteStructure> modularBottomEven;

    QString structureFolderPath;
    QString smallSpritesFolder = "small/";
    QString mediumSpritesFolder = "medium/";
    QString largeSpritesFolder = "large/";
    QString veryLargeSpritesFolder = "veryLarge/";
    QString modularTopOddFolder = "modular/odd/top";
    QString modularMiddleOddFolder = "modular/odd/middle";
    QString modularBottomOddFolder = "modular/odd/bottom";
    QString modularTopEvenFolder = "modular/even/top";
    QString modularMiddleEvenFolder = "modular/even/middle";
    QString modularBottomEvenFolder = "modular/even/bottom";

    QImage setAllRegionColors(SpriteStructure);
    void setRegionColor(CoordinateList region, SpriteStructure& ss, QColor color);

    SpriteStructure getModularSprite();
    SpriteStructure constructModularSprite(bool evenOrOdd, SpriteStructure top, SpriteStructure middle, SpriteStructure bottom);

    void getAllSpriteStructures();
    std::vector<SpriteStructure> getSpriteStructuresFromFolder(QString folderPath);
    SpriteStructure getSpriteStructureFromFile(QString filePath);
};

#endif // ENEMYSPRITEGENERATOR_H
