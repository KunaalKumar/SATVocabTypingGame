#include "enemy.h"

Enemy::Enemy(int baseSpeed)
{
    word = Load::getWord();
    // TO FIX: starting x,y
    int x = 0;
    int y = 0;
    speed = baseSpeed - (word.length() - 1);
}

std::string Enemy::getWord()
{
    return word;
}

double Enemy::distanceTo(int otherX, int otherY)
{
    int xDiff = otherX - x;
    int yDiff = otherY - y;
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
