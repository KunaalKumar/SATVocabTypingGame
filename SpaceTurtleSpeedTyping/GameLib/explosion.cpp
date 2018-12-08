#include "explosion.h"


namespace GameObjects
{
    Explosion::Explosion(posTuple pos) : GameObject (pos)
    {
        type = Type::explosion;
        numOfFrames = 0;
        this->imagePath = "../src/Images/cute_turtle.png";
    }

    posTuple Explosion::getPos()
    {
        numOfFrames++;
        return {posX, posY};
    }

    unsigned int Explosion::getNumOfFrames() { return numOfFrames; }


}
