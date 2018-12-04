#include "stats.h"


Stats::Stats()
{
    round = 0;
    totalTypeCount = 0;
    correctTypeCount = 0;
    totalKillCount = 0;
}

void Stats::addRound() {
    round++;
}

int Stats::getRound() {
    return round;
}

void Stats::addTypeCount(bool isCorrectLetter) {
    if(isCorrectLetter) {
        totalTypeCount++;
        correctTypeCount++;
    } else {
        totalTypeCount++;
    }
}

double Stats::getCorrectRate() {
    if(totalTypeCount == 0) {
        return 0.0;
    } else {
        return correctTypeCount / totalTypeCount;
    }
}

int Stats::getTotalType() {
    return totalTypeCount;
}

int Stats::getCorrectType() {
    return correctTypeCount;
}

void Stats::addTotalKill() {
    totalKillCount++;
}

int Stats::getTotalKill() {
    return totalKillCount;
}
