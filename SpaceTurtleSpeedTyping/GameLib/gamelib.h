#ifndef GAMELIB_H
#define GAMELIB_H

#include "gamelib_global.h"
#include "enemy.h"

#include <string>
#include <float.h>
#include <vector>


class GAMELIBSHARED_EXPORT GameLib
{

    public:
        /* GameLib */
        GameLib();
        ~GameLib();

        /* Enemies */
        void startRound();

        using hitEnemy = bool;
        hitEnemy shoot(char letter);

        void createEnemies(); // I don't think this is necessary, GameLib should decide when will create the Enemies
        // getEnemiesPos();

        /* Player Status */
        int getScore();
        int getLife();
        void setLife(int lifeNum);

        /* Load */
        void setNewDictionary(std::string dictionary);

    private:
        // goes back to zero on a missed shot
        // !!!!!! Should those move to the new status.h file?
        int round;
        int hitStreak; // is this necessary?
        int totalShotCount;
        int correctShotCount;
        int totalKillCount;
        DrawableObjects::Enemy *currentEnemy;
        std::vector<DrawableObjects::Enemy> currentEnemies;
        std::vector<DrawableObjects::DrawableObject> gameObjects;

};

#endif // GAMELIB_H
