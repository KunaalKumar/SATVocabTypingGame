#include "projectile.h"


namespace GameObjects
{
    Projectile::Projectile(posTuple pos, b2Body &projectileBody, b2Body &targetBody) : GameObject(pos, projectileBody),
        projectileBody(projectileBody),
        targetBody(targetBody)
    {
        type = Type::projectile;

    }

}
