#ifndef PLAYER_H
#define PLAYER_H

#include "drawableobjects.h"

namespace DrawableObjects {

    class Player : DrawableObject
    {
        public:
            Player(unsigned int health, posTuple pos);
            Player();
            void removeLife();

        private:
            unsigned int health;
    };

}

#endif // PLAYER_H
