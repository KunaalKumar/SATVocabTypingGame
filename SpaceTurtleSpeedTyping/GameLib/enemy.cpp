#include "enemy.h"


namespace GameObjects {

    Enemy::Enemy(int speed, std::string word, int enemyImageWidth, QImage image, GameObjects::posTuple pos, b2Body &body):
        GameObject (pos, body)
    {
        this->word = word;
        this->enemyImageWidth = enemyImageWidth;
        type = Type::enemy;
        this->speed = (float)speed - (word.length() - 1);
        this->image = image;
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

    bool TargetedEnemy::wasDestroyed()
    {
        return currentLetterPos == word.length() - 1;
    }

}
