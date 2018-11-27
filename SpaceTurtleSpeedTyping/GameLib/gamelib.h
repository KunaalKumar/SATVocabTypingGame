#ifndef GAMELIB_H
#define GAMELIB_H

#include "gamelib_global.h"
#include "enemy.h"

#include <vector>
#include <QTimer>
#include <QObject>


class GAMELIBSHARED_EXPORT GameLib: QObject
{
    Q_OBJECT

public:
    GameLib();
    void startRound();

private slots:
    void createEnemies();

private:
    // goes back to zero on a missed shot
    int round;
    int hitStreak;
    int totalShotCount;
    int correctShotCount;
    int totalKillCount;
    std::vector<Enemy> currentEnemies;


};

#endif // GAMELIB_H
