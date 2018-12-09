#include "enemy.h"
#include <math.h>

namespace GameObjects {

    Enemy::Enemy(int speed, std::string word, std::string imagePath, int boxWidth, GameObjects::posTuple pos, b2Body &body):
        GameObject (pos, body)
    {
        this->word = word;
        this->boxWidth = boxWidth;
        type = Type::enemy;
        this->speed = (float)speed - (word.length() - 1);

        this->imagePath = imagePath;
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

    double Enemy::getRotation(GameObject *player)
    {
        posTuple playerPos = player->getPos();
        posTuple thisPos = this->getPos();
        int x = std::get<0>(thisPos) - std::get<0>(playerPos);
        int y = std::get<1>(thisPos) - std::get<1>(playerPos);

        return atan(y/x);
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

// Targeted Enemy

    TargetedEnemy::TargetedEnemy(Enemy &enemy) : Enemy(enemy)
    {
        type = GameObjects::Type::targetedEnemy;
        currentLetterPos = 0;
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
