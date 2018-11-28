#ifndef ENEMY_H
#define ENEMY_H

#include "load.h"
#include "drawableobjects.h"

#include <math.h>
#include <string>

namespace DrawableObjects {

class Enemy : private DrawableObject
{
    public:
        Enemy(int baseSpeed, posTuple pos);
        Enemy(int baseSpeed);

        using hitPlayer = bool;
        hitPlayer shoot(char letter);

        std::string getWord();
        double distanceTo(int otherX, int otherY);
        bool startsWith(char letter);

    private:
        std::string word;
        int speed;
        unsigned int currentLetterPos;
};

}

#endif // ENEMY_H
