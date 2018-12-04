#include "explosion.h"

namespace GameObjects
{
    explosion::explosion(posTuple pos, b2Body &body) : GameObject (pos, body)
    {
        type = Type::explosion;
    }

}
