#ifndef ENEMY_H
#define ENEMY_H

#include "loadwords.h"
#include "gameobjects.h"

#include "spritegenerator.h"

#include <QDir>
#include <math.h>
#include <string>

namespace GameObjects
{
    class Enemy : public GameObject
    {
        public:
            Enemy(int speed, std::string word, std::string imagePath, int boxWidth, GameObjects::posTuple pos, b2Body &body);

            std::string getWord();
            double distanceTo(GameObjects::posTuple);
            bool startsWith(char letter);
            double getRotation(GameObjects::GameObject* player);

            static int getSize(int wordLength);

        protected:
            std::string word;
            float speed;
            int boxWidth;
    };

    class TargetedEnemy : public Enemy
    {
        public:
            TargetedEnemy(Enemy &enemy);

            using hitPlayer = bool;
            hitPlayer shoot(char letter);

            unsigned int getCurrentLetterPos();
            void resetWord();
            bool wasDestroyed();
        private:
            unsigned int currentLetterPos;
    };

}

#endif // ENEMY_H
