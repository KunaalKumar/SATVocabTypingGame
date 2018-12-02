#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "gameobjects.h"

namespace GameObjects
{

    class explosion : protected GameObject
    {
    public:
        explosion(posTuple pos);
    };

}

#endif // EXPLOSION_H
