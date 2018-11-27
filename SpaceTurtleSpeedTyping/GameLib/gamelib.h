#ifndef GAMELIB_H
#define GAMELIB_H

#include "gamelib_global.h"
#include "enemy.h"

#include <float.h>
#include <vector>
#include <QTimer>
#include <QObject>


class GAMELIBSHARED_EXPORT GameLib: QObject
{
    Q_OBJECT

public:
    GameLib();
    ~GameLib();
    void startRound();
    bool shoot(QString letter);
    void createEnemies();

private:
    // goes back to zero on a missed shot
    int round;
    int hitStreak;
    int totalShotCount;
    int correctShotCount;
    int totalKillCount;
    Enemy *currentEnemy;
    std::vector<Enemy> currentEnemies;


};

#endif // GAMELIB_H
