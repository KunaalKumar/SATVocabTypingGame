#ifndef STATS_H
#define STATS_H

//#include "player.h"
#include <fstream>
#include <string>
#include <vector>
class Stats
{
    public:
        Stats();

        void addRound();
        int getRound();
        void addTypeCount(bool isCorrectLetter);
        double getCorrectRate();
        int getTotalType();
        int getCorrectType();
        void addTotalKill();
        int getTotalKill();

        // todo: streak of letters(If it is wrong go back to 0)
        // todo: load stats text file 3 highest scores
        bool highScore(bool isGameDone, int score);

    private:
        int round;
        int totalTypeCount;
        int correctTypeCount;
        int totalKillCount;
};

#endif // STATS_H
