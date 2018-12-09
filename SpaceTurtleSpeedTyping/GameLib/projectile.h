#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "gameobjects.h"
#include <Box2D/Box2D.h>
#include "enemy.h"

namespace GameObjects
{

    class Projectile : public GameObject
    {
        public:
            Projectile(posTuple pos, b2Body &projectileBody, GameObjects::TargetedEnemy* targetEnemy, b2Body *targetBody, bool killShot);
            b2Body *getTargetBody();
            GameObjects::TargetedEnemy *getTargetedEnemy();
            bool getKillShot();
        private:
            posTuple pos;
            b2Body &projectileBody;
            b2Body *targetBody;
            GameObjects::TargetedEnemy *targetEnemy;
            bool killShot;
    };

}

#endif // PROJECTILE_H
