#ifndef ENEMY_H
#define ENEMY_H

#include "loadwords.h"
#include "gameobjects.h"

#include <math.h>
#include <string>

namespace GameObjects {

class Enemy : private GameObject
{
    public:
        Enemy(int baseSpeed, posTuple pos);

        using hitPlayer = bool;
        hitPlayer shoot(char letter);

        std::string getWord();
        double distanceTo(GameObjects::posTuple);
        bool startsWith(char letter);

    private:
        std::string word;
        int speed;
        unsigned int currentLetterPos;
};

}

#endif // ENEMY_H
