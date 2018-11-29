#include "gamelib.h"
#include  "gameobjects.h"


GameLib::GameLib()
{
}

GameLib::~GameLib()
{
}

std::vector<GameObjects::GameObject>& GameLib::getGameObject() {
    return gameObjects;
}

Stats& GameLib::getStats() {
    return statistic;
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

bool GameLib::shoot(char letter)
{

}

void GameLib::setNewDictionary(std::string dictionary) {

}




