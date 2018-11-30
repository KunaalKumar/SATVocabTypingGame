#include "objectcontroller.h"

ObjectController::ObjectController()
{

}

void ObjectController::createRoundOfEnemies(int round)
{
    LoadWords::createRoundWords(round);
}

void ObjectController::createEnemy(int round)
{
    GameObjects::Enemy enemy(round, {0,0});
    if (enemy.getWord() != "")
    {
        currentEnemies.push_back(enemy); /*adding comment for claification, calling the default connstructor of enemy will give a starting pos of 0,0
                                                                          but a position can be specified by providing a tuple<unsigned int, usigned int> - which can be done with {,}*/
    }
}

//bool ObjectController::shoot(char letter)
//{
//    if (targetedEnemy == nullptr)
//    {
//        // shoot closest enemy with starting letter = letter
//        //TO FIX: put in real user position
//        int userX = 300;
//        int userY = 600;
//        double lowestDistance = DBL_MAX;
//        for (GameObjects::Enemy enemy : currentEnemies)
//        {
//            if (enemy.startsWith(letter))
//            {
//                double distance = enemy.distanceTo(userX, userY);

//                if (distance < lowestDistance)
//                {
//                    lowestDistance = distance;
//                    targetedEnemy = &enemy;
//                }
//            }
//        }
//        if (targetedEnemy != nullptr)
//        {
//            targetedEnemy->shoot(letter);
//        }
//        return targetedEnemy == nullptr;
//    }
//    else
//    {
//        return targetedEnemy->shoot(letter);
//    }
//}
