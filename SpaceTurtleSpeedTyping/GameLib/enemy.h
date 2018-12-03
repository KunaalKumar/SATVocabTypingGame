#ifndef ENEMY_H
#define ENEMY_H

#include "loadwords.h"
#include "gameobjects.h"

#include <math.h>
#include <string>

namespace GameObjects {

    class Enemy : public GameObject
    {
        public:
            Enemy(const Enemy& enemy);
            Enemy(int baseSpeed, posTuple pos, std::string word, QImage image);

            std::string getWord();
            double distanceTo(GameObjects::posTuple);
            bool startsWith(char letter);

        protected:
            std::string word;
            int speed;
    };

    class TargetedEnemy : Enemy
    {
        public:
            TargetedEnemy(Enemy enemy, unsigned int vectorIndex);

            using hitPlayer = bool;
            hitPlayer shoot(char letter);

            bool getVectorIndex();

            bool wasDestroyed();
        private:
            unsigned int currentLetterPos;
            unsigned int vectorIndex;

    };

}

#endif // ENEMY_H
