#ifndef STATUS_H
#define STATUS_H


class Status
{
    public:
        Status();

        void addRound();
        int getRound();
        void addTypeCount(bool isCorrectLetter);
        double getCorrectRate();
        int getTotalType();
        int getCorrectType();
        void addTotalKill();
        int getTotalKill();

    private:
        int round;
        int totalTypeCount;
        int correctTypeCount;
        int totalKillCount;
};

#endif // STATUS_H
