#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "gameobjects.h"
#include <Box2D/Box2D.h>

namespace GameObjects
{

    class Projectile : public GameObject
    {
        public:
            Projectile(posTuple pos, b2Body &projectileBody, b2Body &targetBody);
        private:
            posTuple pos;
            b2Body &projectileBody;
            b2Body &targetBody;
    };

}

#endif // PROJECTILE_H
