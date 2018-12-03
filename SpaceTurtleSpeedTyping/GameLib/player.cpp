#include "player.h"

namespace GameObjects {

Player::Player(posTuple pos, b2Body &body) : GameObject(pos, body)
{
    // this->image =
    this->health = 3;
    this->type = Type::player;
}

}
