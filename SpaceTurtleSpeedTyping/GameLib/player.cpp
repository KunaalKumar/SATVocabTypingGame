#include "player.h"

namespace DrawableObjects {

Player::Player() : DrawableObject()
{
    this->health = 3;
    this->type = Type::player;
}

Player::Player(unsigned int health, posTuple pos) : DrawableObject(pos)
{
    this->health = health;
}

}
