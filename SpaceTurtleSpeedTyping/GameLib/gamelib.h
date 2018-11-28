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

        /* Load */
        void setNewDictionary(std::string dictionary);

        // soren: should move to enemy class
        void createEnemies();
        // getEnemiesPos();


    private:
        std::vector<GameObjects::GameObject> gameObjects;
        Stats statistic;

        // soren: Please move all the things related to enemy class into enemy class
        // Jack will remove all the things later, so pls move all the useful code
        int round;
        int hitStreak; // is this necessary?
        int totalShotCount;
        int correctShotCount;
        int totalKillCount;
        GameObjects::Enemy *currentEnemy;
        std::vector<GameObjects::Enemy> currentEnemies;

};

#endif // GAMELIB_H
