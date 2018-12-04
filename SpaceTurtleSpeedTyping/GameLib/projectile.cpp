#include "projectile.h"

namespace GameObjects {

    Projectile::Projectile(posTuple pos, b2Body &body) : GameObject(pos, body)
    {
    //    this->image =
        type = Type::projectile;
    }

}
