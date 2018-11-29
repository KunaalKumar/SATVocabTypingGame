#include "player.h"

namespace GameObjects {

Player::Player() : GameObject()
{
    this->health = 3;
    this->type = Type::player;
}

Player::Player(unsigned int health, posTuple pos) : GameObject(pos)
{
    this->health = health;
    this->type = Type::player;
}

void Player::removeLife(){
    health--;
}

}
