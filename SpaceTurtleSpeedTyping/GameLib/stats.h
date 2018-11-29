#ifndef STATS_H
#define STATS_H

//#include "player.h"
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
        //void loseLife();

        // todo: streak
        // todo: load stats

    private:
        int round;
        int totalTypeCount;
        int correctTypeCount;
        int totalKillCount;
};

#endif // STATS_H
