#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "gameobjects.h"
#include "enemy.h"
#include <Box2D/Box2D.h>

namespace GameObjects
{

    class Explosion : public GameObject
    {
    public:
        Explosion(posTuple pos);
        posTuple getPos();
        unsigned int getNumOfFrames();
    private:
        unsigned int numOfFrames;
    };

}

#endif // EXPLOSION_H
