#include "enemy.h"

namespace DrawableObjects {

Enemy::Enemy(int baseSpeed, posTuple pos) : DrawableObject(pos)
{
    word = Load::getWord();
    type = Type::enemy;
    speed = baseSpeed - (word.length() - 1);
    currentLetterPos = 0;
}

Enemy::Enemy(int baseSpeed) : DrawableObject ()
{
    word = Load::getWord();
    speed = baseSpeed - (word.length() - 1);
    currentLetterPos = 0;
}

std::string Enemy::getWord()
{
    return word;
}

double Enemy::distanceTo(int otherX, int otherY)
{
    int xDiff = otherX - posX;
    int yDiff = otherY - posY;
    return pow((xDiff*xDiff)+(yDiff*yDiff), 0.5);
}

bool Enemy::startsWith(std::string letter)
{
    return letter == word.substr(0, 1);
}

bool Enemy::shoot(std::string letter)
{
    if (letter == word.substr(0, 1))
    {
        int newLength = word.length()-1;
        word = word.substr(1, newLength);
        return true;
    }
    return false;
}

}
