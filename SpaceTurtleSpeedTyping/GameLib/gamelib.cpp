#include "gamelib.h"
#include "gameobjects.h"


GameLib::GameLib()
{
}

GameLib::~GameLib()
{
}

std::vector<GameObjects::GameObject>& GameLib::getGameObject() {
    return gameObjects;
}

std::map<std::string, double>& GameLib::getStats() {
    // return ;
}

void GameLib::startRound()
{
    statistic.addRound();
    //todo
}

bool GameLib::isEndRound() {

}

void GameLib::updateFrame() {

}

bool GameLib::letterTyped(char letter)
{

}

void GameLib::setNewDictionary(std::string dictionary) {

}




