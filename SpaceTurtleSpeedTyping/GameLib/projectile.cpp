#include "projectile.h"

namespace DrawableObjects {

Projectile::Projectile(posTuple pos) : DrawableObject(pos)
{
    type = Type::projectile;
}

}
