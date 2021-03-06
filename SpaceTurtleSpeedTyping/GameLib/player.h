#ifndef PLAYER_H
#define PLAYER_H

#include "gameobjects.h"
#include <Box2D/Box2D.h>

namespace GameObjects
{
    class Player : public GameObject
    {
        public:
            Player(posTuple pos, b2Body &body);

            int getHealth();
            void addHealth();
            void removeHealth();

        private:
            unsigned int health;
    };
}

#endif // PLAYER_H
