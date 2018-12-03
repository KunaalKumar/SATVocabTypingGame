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
            GameObject(unsigned int posX, unsigned int posY, b2Body body)
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

            b2Body& getBody() {
                return *body;
            }

        private:
            // Sets the values of the x,y positions to the latest b2Body positions
            void updatePos() {
                posX = body->GetPosition().x;
                posY = body->GetPosition().y;
            }


        protected:
            unsigned int posX;
            unsigned int posY;
            Type type;
            QImage image;
            b2Body *body;
    };

}

#endif // DRAWABLEOBJECTS_H
