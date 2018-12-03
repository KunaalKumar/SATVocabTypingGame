#include "gamelib.h"
#include "gameobjects.h"
#include "loadwords.h"


GameLib::GameLib(int x, int y)
{
    //todo
    oc = new ObjectController(x, y);
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
//    if(oc.isRoundEnd()) {
//
//    } else {
//
//    }
}

bool GameLib::isEndGame(){

}

void GameLib::updateFrame() {
        // todo: oc
}

void GameLib::letterTyped(char letter)
{
    if (oc->letterTyped(letter)) {
        statistic.addTypeCount(true);
        // if(oc. isEnemyDestroyed()) {
        //    statistic.addTotalKill();
        //}
    } else {
        statistic.addTypeCount(false);
    }
}

void GameLib::setNewDictionary(std::string dictionary) {

}




