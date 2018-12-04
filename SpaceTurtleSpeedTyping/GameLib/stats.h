#ifndef STATS_H
#define STATS_H

//#include "player.h"
#include <fstream>
#include <string>
#include <vector>
#include <QDebug>
#include <string>
#include <map>

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
        int getKillStreak();
        // todo: load stats text file 3 highest scores
        bool highScore(bool isGameDone, int score);
        const std::map<std::string, double>& getAllStats();


    private:
        int round;
        int totalTypeCount;
        int correctTypeCount;
        int totalKillCount;
        int killStreak;
        std::map<std::string, double> statsMap;
};

#endif // STATS_H
