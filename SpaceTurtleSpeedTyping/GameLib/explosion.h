#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "gameobjects.h"
#include <Box2D/Box2D.h>

namespace GameObjects
{

    class explosion : protected GameObject
    {
    public:
        explosion(posTuple pos, b2Body &body);
    };

}

#endif // EXPLOSION_H
