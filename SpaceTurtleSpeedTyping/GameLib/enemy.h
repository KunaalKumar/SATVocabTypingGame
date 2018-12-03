#ifndef ENEMY_H
#define ENEMY_H

#include "loadwords.h"
#include "gameobjects.h"

#include <math.h>
#include <string>

namespace GameObjects {

    class Enemy : protected GameObject
    {
        public:
            Enemy(int speed, std::string word, QImage image, unsigned int posX, unsigned int posY, b2Body &body, double windowSizeX, double windowSizeY);

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
            TargetedEnemy(Enemy enemy);

            using hitPlayer = bool;
            hitPlayer shoot(char letter);

            bool wasDestroyed();
        private:
            unsigned int currentLetterPos;
    };

}

#endif // ENEMY_H
