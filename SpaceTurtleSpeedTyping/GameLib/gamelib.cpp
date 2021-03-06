#include "gamelib.h"
#include "gameobjects.h"
#include "loadwords.h"


GameLib::GameLib(int x, int y, bool hard):oc(x, y, hard)  { }

GameLib::~GameLib() { }

const std::vector<GameObjects::GameObject *>& GameLib::getGameObject()
{
    return oc.getObjects();
}

const std::map<std::string, double>& GameLib::getStats()
{
    return statistic.getAllStats();
}

void GameLib::startRound()
{
    statistic.addRound();
    oc.createRoundOfEnemies(statistic.getRound());
    oc.updateObjectPositions();
}

void GameLib::resetGame()
{
    oc.resetObjects();
}

bool GameLib::isEndRound()
{
    oc.isRoundEnd();
}

bool GameLib::isEndGame()
{
    oc.isEndGame();
}

void GameLib::updateFrame()
{
    oc.updateObjectPositions();
}

bool GameLib::letterTyped(char letter)
{
    if (oc.letterTyped(letter))
    {
        statistic.addTypeCount(true);
        if(oc.isEnemyKilled()) {
            statistic.addTotalKill();
        }
        return true;
    }
    else
    {
        statistic.addTypeCount(false);
    }
    return false;
}

double GameLib::getStatRound(){
    return statistic.getRound();
}

GameObjects::Player *GameLib::getPlayer()
{
    return oc.getPlayer();
}

double GameLib::getStatKillStreak(){
    return statistic.getLongestHitStreak();
}

double GameLib::getStatTotalScore(){
    return statistic.getTotalKill();
}

double GameLib::getStatHitRate()
{
    return statistic.getCorrectRate();
}

void GameLib::setNewDictionary(std::string dictionary)
{

}
