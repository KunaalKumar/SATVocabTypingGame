#ifndef STATS_H
#define STATS_H

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

        const std::map<std::string, double>& getAllStats();


        // todo: streak
        // todo: load stats

    private:
        int round;
        int totalTypeCount;
        int correctTypeCount;
        int totalKillCount;
        std::map<std::string, double> statsMap;
};

#endif // STATS_H
