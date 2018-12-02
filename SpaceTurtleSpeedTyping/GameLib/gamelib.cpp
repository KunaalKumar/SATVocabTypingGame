#include "gamelib.h"
#include "gameobjects.h"
#include "loadwords.h"


GameLib::GameLib(int x, int y)
{
    //todo
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

bool GameLib::isEndGame(){

}

void GameLib::updateFrame() {

}

void GameLib::letterTyped(char letter)
{

}

void GameLib::setNewDictionary(std::string dictionary) {

}




