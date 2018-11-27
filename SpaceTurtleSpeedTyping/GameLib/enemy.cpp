#include "enemy.h"

Enemy::Enemy(int baseSpeed)
{
    word = Load::getWord();
    QPoint position(0, 0);
    speed = baseSpeed - (word.length() - 1);
}

std::string Enemy::getWord()
{
    return word;
}

QPoint Enemy::getPosition()
{
    return position;
}

double Enemy::distanceTo(QPoint other)
{
    int x = other.rx() - this->position.rx();
    int y = other.ry() - this->position.ry();
    return pow((x*x)+(y*y), 0.5);
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
