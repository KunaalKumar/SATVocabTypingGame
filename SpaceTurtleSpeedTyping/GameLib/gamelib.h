#ifndef GAMELIB_H
#define GAMELIB_H

#include "gamelib_global.h"
#include "enemy.h"
#include "stats.h"
#include "load.h"

#include <string>
#include <float.h>
#include <vector>


class GAMELIBSHARED_EXPORT GameLib
{

    public:

        /* GameLib */
        GameLib();
        ~GameLib();

        /* Objects */
        std::vector<GameObjects::GameObject> getGameObject();
        Stats getStats();

        /* Game */
        void startRound();

        void updateFrame();

        using hitEnemy = bool;
        hitEnemy shoot(char letter);

        // should move to enemy class
        void createEnemies(); // I don't think this is necessary, GameLib should decide when will create the Enemies
        // getEnemiesPos();

        /* Load */
        void setNewDictionary(std::string dictionary);

    private:
        std::vector<GameObjects::GameObject> gameObjects;
        Stats statistic;

        // goes back to zero on a missed shot
        // !!!!!! Should those move to the new status.h file?
        int round;
        int hitStreak; // is this necessary?
        int totalShotCount;
        int correctShotCount;
        int totalKillCount;
        GameObjects::Enemy *currentEnemy;
        std::vector<GameObjects::Enemy> currentEnemies;

};

#endif // GAMELIB_H
