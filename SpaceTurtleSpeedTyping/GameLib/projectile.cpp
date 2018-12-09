#include "projectile.h"


namespace GameObjects
{
    Projectile::Projectile(posTuple pos, b2Body &projectileBody,GameObjects::TargetedEnemy *targetEnemy, b2Body *targetBody, bool killShot) : GameObject(pos, projectileBody),
        projectileBody(projectileBody),
        targetBody(targetBody),
        killShot(killShot),
        targetEnemy(targetEnemy)
    {
        type = Type::projectile;

    }

    b2Body *Projectile::getTargetBody()
    {
        return targetBody;
    }

    TargetedEnemy *Projectile::getTargetedEnemy()
    {
        return targetEnemy;
    }

    bool Projectile::getKillShot()
    {
        return killShot;
    }

}
