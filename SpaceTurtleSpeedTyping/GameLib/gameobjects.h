#ifndef DRAWABLEOBJECTS_H
#define DRAWABLEOBJECTS_H

#include <QImage>
#include <tuple>
#include <string>
#include <Box2D/Box2D.h>

namespace GameObjects {

    using posTuple = std::tuple<unsigned int, unsigned int>;

    enum class Type
    {
        projectile,
        enemy,
        targetedEnemy,
        player,
        explosion
    };


    class GameObject
    {
        public:
            GameObject(unsigned int posX, unsigned int posY, b2Body &body, double windowSizeX, double windowSizeY)
            {
                this->posX = posX;
                this->posY = posY;
                this->body = &body;
                this->windowSizeX = windowSizeX;
                this->windowSizeY = windowSizeY;
            }

            GameObject(posTuple pos)
            {
                posX = std::get<0>(pos);
                posY = std::get<1>(pos);
            }

            posTuple getPos()
            {
                updatePos();
                // TODO: Convert using window size to QtWindow coordinates
                return {posX, posY};
            }

        private:
            // Sets the values of the x,y positions to the latest b2Body positions
            void updatePos() {
                posX = body->GetPosition().x + windowSizeX;
                posY = body->GetPosition().y + windowSizeY;
            }


        protected:
            unsigned int posX;
            unsigned int posY;
            double windowSizeX;
            double windowSizeY;
            Type type;
            QImage image;
            b2Body *body;
    };

}

#endif // DRAWABLEOBJECTS_H
