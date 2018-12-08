#ifndef GAMELIB_H
#define GAMELIB_H

#include "objectcontroller.h"
#include "stats.h"

#include <string>
#include <float.h>
#include <vector>
#include <map>


class GameLib
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
        const std::vector<GameObjects::GameObject *>& getGameObject();

        /*
         * "round"
         * "correctRate"
         * "totalKill"
         * "killStreak"
         * "currentScore"
         * "highScore"
         */
        const std::map<std::string, double>& getStats();

        /* >>>>>>>>>> Game <<<<<<<<<< */
        void startRound();

        bool isEndRound();
        bool isEndGame();

        void updateFrame();
        void leaveGame();

        /* When user input, use this API */
        bool letterTyped(char letter);

        /* Methods to get stats numbers cause maps dont work*/
        double getStatTotalScore();
        double getStatKillStreak();
        double getStatRound();

        /* >>>>>>>>>> Load <<<<<<<<<< */
        void setNewDictionary(std::string dictionary);
private:
        std::vector<GameObjects::GameObject> gameObjects;
        Stats statistic;
        ObjectController oc;
};

#endif // GAMELIB_H
