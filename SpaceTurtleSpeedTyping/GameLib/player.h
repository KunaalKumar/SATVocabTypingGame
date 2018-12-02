#ifndef PLAYER_H
#define PLAYER_H

#include "gameobjects.h"

namespace GameObjects {

    class Player : public GameObject
    {
        public:
            Player(posTuple pos);
            Player();

            int getHealth();
            void addHealth();
            void removeHealth();

        private:
            unsigned int health;
    };

}

#endif // PLAYER_H
