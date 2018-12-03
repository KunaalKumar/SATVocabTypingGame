#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "gameobjects.h"
#include <Box2D/Box2D.h>

namespace GameObjects
{

    class Projectile : public GameObject
    {
        public:
            Projectile(posTuple pos, b2Body &body);
        private:
            //
    };

}

#endif // PROJECTILE_H
