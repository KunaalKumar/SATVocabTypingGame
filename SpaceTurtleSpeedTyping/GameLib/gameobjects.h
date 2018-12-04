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
            GameObject(posTuple pos, b2Body &body)
            {
                this->posX = std::get<0>(pos);
                this->posY = std::get<1>(pos);
                this->body = &body;
            }

            posTuple getPos()
            {
                updatePos();
                // TODO: Convert using window size to QtWindow coordinates
                return {posX, posY};
            }

            QImage getImage() { return image; }

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
