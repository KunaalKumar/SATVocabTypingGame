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
    /**
         * @brief GameLib
         * @param x - size of widnow: x axis
         * @param y - size of widnow: y axis
         */
        GameLib(int x, int y);
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
        bool isEndGame();

        void updateFrame();

        /* When user input, use this API */
        void letterTyped(char letter);

        /* >>>>>>>>>> Load <<<<<<<<<< */
        void setNewDictionary(std::string dictionary);

    private:
        std::vector<GameObjects::GameObject> gameObjects;
        Stats statistic;
        ObjectController oc;
};

#endif // GAMELIB_H
