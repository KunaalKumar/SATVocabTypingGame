#ifndef ENEMY_H
#define ENEMY_H

#include "load.h"

#include <math.h>
#include <string>

class Enemy
{
public:
    Enemy(int baseSpeed);

    // returns whether or not enemy was hit
    bool shoot(std::string letter);
    std::string getWord();
    double distanceTo(int otherX, int otherY);
    bool startsWith(std::string letter);

private:
    std::string word;
    int x;
    int y;
    int speed;


};

#endif // ENEMY_H
