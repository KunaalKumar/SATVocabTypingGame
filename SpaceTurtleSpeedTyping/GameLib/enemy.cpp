#include "enemy.h"
namespace GameObjects {

TargetedEnemy::TargetedEnemy(Enemy enemy) : Enemy(enemy)
{
//    image =
    currentLetterPos = 0;
}

Enemy::Enemy(int speed, std::string word, QImage image, float posX, float posY, b2Body &body):
    GameObject (posX, posY, body)
{
    this->word = word;
    type = Type::enemy;
    this->speed = (float)speed - (word.length() - 1);
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

bool TargetedEnemy::shoot(char letter)
{
    if (letter == word[currentLetterPos])
    {
        currentLetterPos++;
        return true;
    }
    return false;
}

bool TargetedEnemy::wasDestroyed()
{
    return currentLetterPos == word.length() - 1;
}

}
