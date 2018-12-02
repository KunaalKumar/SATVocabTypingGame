#include "enemy.h"

namespace GameObjects {

Enemy::Enemy(int baseSpeed, posTuple pos) : GameObject(pos)
{
    word = LoadWords::getWord();
    type = Type::enemy;
    speed = baseSpeed - (word.length() - 1);
    currentLetterPos = 0;
}

std::string Enemy::getWord()
{
    return word;
}

double Enemy::distanceTo(GameObjects::posTuple otherPos)
{
    int xDiff = std::get<0>(otherPos) - posX;
    int yDiff = std::get<1>(otherPos) - posY;
    return pow((xDiff*xDiff)+(yDiff*yDiff), 0.5);
}

bool Enemy::startsWith(char letter)
{
    return letter == word[0];
}

bool Enemy::shoot(char letter)
{
    if (letter == word[0])
    {
        int newLength = word.length()-1;
        word = word.substr(1, newLength);
        return true;
    }
    return false;
}

}
