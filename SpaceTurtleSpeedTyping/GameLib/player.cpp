#include "player.h"

namespace DrawableObjects {

Player::Player() : DrawableObject()
{
    this->health = 3;
}

Player::Player(unsigned int health, posTuple pos) : DrawableObject(pos)
{
    this->health = health;
}

}
