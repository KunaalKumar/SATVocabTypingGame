#include "projectile.h"

namespace GameObjects {

    Projectile::Projectile(posTuple pos) : GameObject(pos)
    {
    //    this->image =
        type = Type::projectile;
    }

}
