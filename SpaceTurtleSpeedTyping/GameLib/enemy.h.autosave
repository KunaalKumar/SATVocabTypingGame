#ifndef ENEMY_H
#define ENEMY_H

#include "load.h"
#include "gameobjects.h"

#include <math.h>
#include <string>

namespace GameObjects {

class Enemy : private GameObject
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
