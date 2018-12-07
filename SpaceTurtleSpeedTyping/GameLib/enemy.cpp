#include "enemy.h"
#include <QDebug>

namespace GameObjects {

    Enemy::Enemy(int speed, std::string word, int boxWidth, GameObjects::posTuple pos, b2Body &body):
        GameObject (pos, body)
    {
        this->word = word;
        this->boxWidth = boxWidth;
        type = Type::enemy;
        this->speed = (float)speed - (word.length() - 1);

        //this->imagePath = Enemy::imagePaths.at(Enemy::imagePathIndex++);
        this->imagePath = "../src/Images/cute_turtle.png";
    }

    std::string Enemy::getWord()
    {
        return word;
    }

    double Enemy::distanceTo(GameObjects::posTuple otherPos)
    {
        float xDiff = std::get<0>(otherPos) - posX;
        float yDiff = std::get<1>(otherPos) - posY;
        return pow((xDiff*xDiff)+(yDiff*yDiff), 0.5);
    }

    bool Enemy::startsWith(char letter)
    {
        return letter == word[0];
    }

    // Static
    int Enemy::getSize(int wordLength)
    {
        switch (wordLength)
        {
            case 3 ... 5  : return 32;
            case 6 ... 8  : return 48;
            case 9 ... 11 : return 64;
            default       : return 128;
        }
    }

//    void Enemy::initSpriteGenerator()
//    {
//        QDir relativeDir(QDir::currentPath());
//        relativeDir.cdUp();
//        relativeDir.cd("SpriteStructures/");
//        Enemy::sg = SpriteGenerator(relativeDir.path() + '/');
//    }

//    void Enemy::createImagePaths()
//    {
//        Enemy::imagePathIndex = 0;
//        //QImage sprite = sg.generatreNewSprite(SpriteSize::small);
//        // Set starting position dynamically when creating enemy objects based on window size
//        //
//    }

// Targeted Enemy

    TargetedEnemy::TargetedEnemy(Enemy enemy, unsigned int vectorIndex) : Enemy(enemy)
    {
    //    image =
        currentLetterPos = 0;
        this->vectorIndex = vectorIndex;
    }

    bool TargetedEnemy::shoot(char letter)
    {
        if (letter == word[currentLetterPos])
        {
            currentLetterPos++;
            return true;
        }
        return false;
    }

    unsigned int TargetedEnemy::getVectorIndex()
    {
        return vectorIndex;
    }

    unsigned int TargetedEnemy::getCurrentLetterPos()
    {
        return currentLetterPos;
    }

    void TargetedEnemy::resetWord()
    {
        currentLetterPos = 0;
    }

    bool TargetedEnemy::wasDestroyed()
    {
        return currentLetterPos == word.length();
    }

}
