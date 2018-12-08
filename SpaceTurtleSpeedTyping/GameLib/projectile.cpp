#include "projectile.h"


namespace GameObjects
{
    Projectile::Projectile(posTuple pos, b2Body &projectileBody, b2Body *targetBody, bool killShot) : GameObject(pos, projectileBody),
        projectileBody(projectileBody),
        targetBody(targetBody),
        killShot(killShot)
    {
        type = Type::projectile;

    }

    b2Body *Projectile::getTargetBody()
    {
        return targetBody;
    }

    bool Projectile::getKillShot()
    {
        return killShot;
    }

}
