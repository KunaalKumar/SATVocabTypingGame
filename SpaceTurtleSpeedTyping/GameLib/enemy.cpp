#include "enemy.h"

Enemy::Enemy(int baseSpeed)
{
    word = Load::getWord();
    QPoint position(0, 0);
    speed = baseSpeed - (word.length() - 1);
}

bool Enemy::shootEnemy(std::string letter)
{

}

std::string Enemy::getWord()
{
    return word;
}
