#ifndef ENEMYSPRITEGENERATOR_H
#define ENEMYSPRITEGENERATOR_H

#include "spritestructures.h"
#include <QDir>


class SpriteGenerator
{
public:
    SpriteGenerator();
    SpriteGenerator(QString filepath,
                    QString ssFolder = "small/",
                    QString msFolder = "medium/",
                    QString lsFolder = "large/",
                    QString vlsFolder = "veryLarge/");

    QImage generatreNewSprite(SpriteSize ss);

private:
    std::vector<SpriteStructure> smallSprites;
    std::vector<SpriteStructure> mediumSprites;
    std::vector<SpriteStructure> largeSprites;
    std::vector<SpriteStructure> veryLargeSprites;

    QString structureFolderPath;
    QString smallSpritesFolder;
    QString mediumSpritesFolder;
    QString largeSpritesFolder;
    QString veryLargeSpritesFolder;

    QImage setAllRegionColors(SpriteStructure);
    void setRegionColor(CoordinateList region, SpriteStructure& ss, QColor color);

    void getAllSpriteStructures();
    std::vector<SpriteStructure> getSpriteStructuresFromFolder(QString folderPath);
    SpriteStructure getSpriteStructureFromFile(QString filePath);
};

#endif // ENEMYSPRITEGENERATOR_H
