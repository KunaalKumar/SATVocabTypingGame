#include "objectcontroller.h"

ObjectController::ObjectController()
{

}

void ObjectController::createRoundOfEnemies()
{
    Load::createRoundWords(++round);
}

void ObjectController::createEnemy()
{
    GameObjects::Enemy enemy(round, {0,0});
    if (enemy.getWord() != "")
    {
        currentEnemies.push_back(enemy); /*adding comment for claification, calling the default connstructor of enemy will give a starting pos of 0,0
                                                                          but a position can be specified by providing a tuple<unsigned int, usigned int> - which can be done with {,}*/
    }
}

bool ObjectController::shoot(char letter)
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
