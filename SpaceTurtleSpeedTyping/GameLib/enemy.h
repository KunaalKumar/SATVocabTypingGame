#ifndef ENEMY_H
#define ENEMY_H

#include "loadwords.h"
#include "gameobjects.h"

#include <math.h>
#include <string>

namespace GameObjects
{

    class Enemy : public GameObject
    {
        public:
            Enemy(int speed, std::string word, int enemyImageWidth, QImage image, GameObjects::posTuple pos, b2Body &body);

            std::string getWord();
            double distanceTo(GameObjects::posTuple);
            bool startsWith(char letter);

        protected:
            std::string word;
            float speed;
            int enemyImageWidth;
    };

    class TargetedEnemy : public Enemy
    {
        public:
            TargetedEnemy(Enemy enemy, unsigned int vectorIndex);

            using hitPlayer = bool;
            hitPlayer shoot(char letter);

            unsigned int getVectorIndex();
            bool wasDestroyed();
        private:
            unsigned int currentLetterPos;
            unsigned int vectorIndex;

    };

}

#endif // ENEMY_H
