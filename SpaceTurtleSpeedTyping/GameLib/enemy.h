#ifndef ENEMY_H
#define ENEMY_H

#include "load.h"

#include <math.h>
#include <string>
#include <QPoint>

class Enemy
{
public:
    Enemy(int baseSpeed);

    // returns whether or not enemy was hit
    bool shoot(std::string letter);
    std::string getWord();
    QPoint getPosition();
    double distanceTo(QPoint other);
    bool startsWith(std::string letter);

private:
    std::string word;
    QPoint position;
    int speed;


};

#endif // ENEMY_H
