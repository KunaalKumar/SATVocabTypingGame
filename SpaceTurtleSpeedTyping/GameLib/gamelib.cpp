#include "gamelib.h"
#include "gameobjects.h"
#include "loadwords.h"


GameLib::GameLib(int x, int y):oc(x, y)
{
}

GameLib::~GameLib()
{

}

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
    oc.updateObjectPositions();
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

void GameLib::letterTyped(char letter)
{
    if (oc.letterTyped(letter))
    {
        statistic.addTypeCount(true);
        if(oc.isEnemyKilled()) {
            statistic.addTotalKill();
        }
    }
    else
    {
        statistic.addTypeCount(false);
    }
}

void GameLib::setNewDictionary(std::string dictionary)
{

}
