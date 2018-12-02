#include "enemy.h"

namespace GameObjects {

TargetedEnemy::TargetedEnemy(Enemy enemy) : Enemy(enemy)
{
//    image =
    currentLetterPos = 0;
}

Enemy::Enemy(const Enemy& enemy)
{
    speed = enemy.speed;
    word = enemy.word;
}

Enemy::Enemy(int baseSpeed, posTuple pos, std::string word, QImage image) : GameObject(pos)
{
    this->word = word;
    type = Type::enemy;
    speed = baseSpeed - (word.length() - 1);
    this->image = image;
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
