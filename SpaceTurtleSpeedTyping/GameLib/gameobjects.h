#ifndef DRAWABLEOBJECTS_H
#define DRAWABLEOBJECTS_H

#include <QImage>
#include <tuple>
#include <string>
#include <Box2D/Box2D.h>
#include "gamelib_global.h"

namespace GameObjects {

    using posTuple = std::tuple<float, float>;

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
            GameObject(float posX, float posY, b2Body &body)
            {
                this->posX = posX;
                this->posY = posY;
                this->body = &body;
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

            bool isOfType(Type other) { return type == other; }

        private:
            // Sets the values of the x,y positions to the latest b2Body positions
            void updatePos() {
                posX = body->GetPosition().x + windowSizeX;
                posY = body->GetPosition().y + windowSizeY;
            }


        protected:
            float posX;
            float posY;
            Type type;
            QImage image;
            b2Body *body;
    };

}

#endif // DRAWABLEOBJECTS_H
