#ifndef GAMELIB_H
#define GAMELIB_H

#include "gamelib_global.h"
#include "objectcontroller.h"
#include "stats.h"

#include <string>
#include <float.h>
#include <vector>
#include <map>


class GAMELIBSHARED_EXPORT GameLib
{

    public:

        /* >>>>>>>>>> GameLib <<<<<<<<<< */
        GameLib();
        ~GameLib();

        /* >>>>>>>>>> Objects <<<<<<<<<< */
        /* GameObject:
         * getPos();
         * getType();
         * getWord();
         */
        std::vector<GameObjects::GameObject>& getGameObject();

        std::map<std::string, double>& getStats();

        /* >>>>>>>>>> Game <<<<<<<<<< */
        void startRound();
        bool isEndRound();

        void updateFrame();

        using hitEnemy = bool;
        hitEnemy letterTyped(char letter);

        bool isEnemyHited();
        GameObjects::posTuple enemyHitedPos();
        bool isEnemyDestoryed();
        GameObjects::posTuple enemyDestoryedPos();

        /* >>>>>>>>>> Load <<<<<<<<<< */
        void setNewDictionary(std::string dictionary);

    private:
        std::vector<GameObjects::GameObject> gameObjects;
        Stats statistic;
        ObjectController oc;
};

#endif // GAMELIB_H
