#include "gamelib.h"


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
    Enemy enemy(round);
    if (enemy.getWord() != "")
    {
        currentEnemies.push_back(Enemy(round));
    }
}

bool GameLib::shoot(QString letter)
{
    if (currentEnemy == nullptr)
    {
        // shoot closest enemy with starting letter = letter
        //TO FIX: put in real user position
        QPoint userPos(600, 300);
        double lowestDistance = DBL_MAX;
        for (Enemy enemy : currentEnemies)
        {
            if (enemy.startsWith(letter.toStdString()))
            {
                double distance = enemy.distanceTo(userPos);

                if (distance < lowestDistance)
                {
                    lowestDistance = distance;
                    currentEnemy = &enemy;
                }
            }
        }
        if (currentEnemy != nullptr)
        {
            currentEnemy->shoot(letter.toStdString());
        }
        return currentEnemy == nullptr;
    }
    else
    {
        return currentEnemy->shoot(letter.toStdString());
    }
}



