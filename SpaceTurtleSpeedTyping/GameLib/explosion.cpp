#include "explosion.h"


namespace GameObjects
{
    Explosion::Explosion(GameObjects::TargetedEnemy& enemy) : GameObject (enemy.getPos())
    {
        type = Type::explosion;
        vectorIndex = enemy.getVectorIndex();
        numOfFrames = 0;
        this->imagePath = "../src/Images/cute_turtle.png";
    }

    posTuple Explosion::getPos()
    {
        numOfFrames++;
        return {posX, posY};
    }

    unsigned int Explosion::getNumOfFrames() { return numOfFrames; }

    unsigned int Explosion::getVectorIndex() { return vectorIndex; }

}
