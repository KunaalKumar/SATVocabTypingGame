#include "gamelib.h"
#include  "gameobjects.h"


GameLib::GameLib()
{
    hitStreak = 0;
    totalShotCount = 0;
    correctShotCount = 0;
    totalKillCount = 0;
}

GameLib::~GameLib()
{
    delete currentEnemy;
}

void GameLib::startRound()
{
    Load::createRoundWords(++round);
}

void GameLib::createEnemies()
{
    GameObjects::Enemy enemy(round);
    if (enemy.getWord() != "")
    {
        currentEnemies.push_back(GameObjects::Enemy(round, {0,0})); /*adding comment for claification, calling the default connstructor of enemy will give a starting pos of 0,0
                                                                          but a position can be specified by providing a tuple<unsigned int, usigned int> - which can be done with {,}*/
    }
}

bool GameLib::shoot(char letter)
{
    if (currentEnemy == nullptr)
    {
        // shoot closest enemy with starting letter = letter
        //TO FIX: put in real user position
        int userX = 300;
        int userY = 600;
        double lowestDistance = DBL_MAX;
        for (GameObjects::Enemy enemy : currentEnemies)
        {
            if (enemy.startsWith(letter))
            {
                double distance = enemy.distanceTo(userX, userY);

                if (distance < lowestDistance)
                {
                    lowestDistance = distance;
                    currentEnemy = &enemy;
                }
            }
        }
        if (currentEnemy != nullptr)
        {
            currentEnemy->shoot(letter);
        }
        return currentEnemy == nullptr;
    }
    else
    {
        return currentEnemy->shoot(letter);
    }
}



