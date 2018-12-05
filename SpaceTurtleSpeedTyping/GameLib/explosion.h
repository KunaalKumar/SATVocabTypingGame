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
        Explosion(GameObjects::TargetedEnemy& enemy);
        posTuple getPos();
        unsigned int getNumOfFrames();
        unsigned int getVectorIndex();
    private:
        unsigned int vectorIndex;
        unsigned int numOfFrames;
    };

}

#endif // EXPLOSION_H
