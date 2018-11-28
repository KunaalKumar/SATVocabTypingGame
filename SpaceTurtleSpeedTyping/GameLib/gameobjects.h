#ifndef DRAWABLEOBJECTS_H
#define DRAWABLEOBJECTS_H

#include <tuple>

namespace GameObjects {

    using posTuple = std::tuple<unsigned int, unsigned int>;

    enum class Type
    {
        projectile,
        enemy,
        player
    };


    class GameObject
    {
        public:
            GameObject()
            {
                posX = 0;
                posY = 0;
            }

            GameObject(posTuple pos)
            {
                posX = std::get<0>(pos);
                posY = std::get<1>(pos);
            }

            posTuple getPos()
            {
                return {posX, posY};
            }

            void setPosX(unsigned int x) { posX = x; }
            void setPosY(unsigned int y) { posY = y; }

        protected:
            unsigned int posX;
            unsigned int posY;
            Type type;
    };

}

#endif // DRAWABLEOBJECTS_H
