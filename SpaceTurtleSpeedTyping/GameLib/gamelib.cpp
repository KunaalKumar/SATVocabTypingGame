#include "gamelib.h"
#include "gameobjects.h"
#include "loadwords.h"


GameLib::GameLib(int x, int y)
{
    windowSizeX = x / 2;
    windowSizeY = y / 2;
}

GameLib::~GameLib()
{
}

const std::vector<GameObjects::GameObject>& GameLib::getGameObject()
{
    return gameObjects;
}

const std::map<std::string, double>& GameLib::getStats()
{
    return statistic.getAllStats();
}

void GameLib::startRound()
{
    statistic.addRound();
    oc.updateObjectPositions(); // todo
}

bool GameLib::isEndRound()
{
    if(oc.isRoundEnd()) {

    } else {

    }
}

bool GameLib::isEndGame()
{

}

void GameLib::updateFrame()
{
        // todo: oc
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




