#ifndef ENEMY_H
#define ENEMY_H

#include "load.h"

#include <string>
#include <QPoint>

class Enemy
{
public:
    Enemy(int baseSpeed);

    // returns whether or not enemy was hit
    bool shootEnemy(std::string letter);
    std::string getWord();

private:
    std::string word;
    QPoint position;
    int speed;


};

#endif // ENEMY_H
