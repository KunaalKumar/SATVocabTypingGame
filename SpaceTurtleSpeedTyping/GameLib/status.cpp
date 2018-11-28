#include "status.h"

Status::Status()
{
    round = 0;
    totalTypeCount = 0;
    correctTypeCount = 0;
    totalKillCount = 0;
}

void Status::addRound() {
    round++;
}

int Status::getRound() {
    return round;
}

void Status::addTypeCount(bool isCorrectLetter) {
    if(isCorrectLetter) {
        totalTypeCount++;
        correctTypeCount++;
    } else {
        totalTypeCount++;
    }
}

double Status::getCorrectRate() {
    if(totalTypeCount == 0) {
        return 0.0;
    } else {
        return correctTypeCount / totalTypeCount;
    }
}

int Status::getTotalType() {
    return totalTypeCount;
}

int Status::getCorrectType() {
    return correctTypeCount;
}

void Status::addTotalKill() {
    totalKillCount++;
}

int Status::getTotalKill() {
    return totalKillCount;
}
