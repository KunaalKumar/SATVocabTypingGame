#include "player.h"

namespace GameObjects {

Player::Player() : GameObject()
{
    this->health = 3;
    this->type = Type::player;
}

Player::Player(posTuple pos) : GameObject(pos)
{
    // this->image =
    this->health = 3;
    this->type = Type::player;
}

}
