#ifndef DRAWABLEOBJECTS_H
#define DRAWABLEOBJECTS_H

#include <QImage>
#include <tuple>
#include <string>
#include <Box2D/Box2D.h>

namespace GameObjects
{
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
            GameObject(posTuple pos)
            {
                this->posX = std::get<0>(pos);
                this->posY = std::get<1>(pos);
                this->body = nullptr;
            }

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

            std::string getImage() { return imagePath; }

            bool isOfType(Type other) { return other == type; }

            std::string getTypeString()
            {
                switch (type)
                {
                    case Type::projectile    : return "projectile";
                    case Type::enemy         : return "enemy";
                    case Type::targetedEnemy : return "target";
                    case Type::player        : return "player";
                    case Type::explosion     : return "explosion";
                }
                return "";
            }

            b2Body* getBody() { return body; }

        private:
            // Sets the values of the x,y positions to the latest b2Body positions
            void updatePos() {
                if(body != nullptr) {
                    posX = body->GetPosition().x*4;
                    posY = -body->GetPosition().y*4;
                }
            }

        protected:
            float posX;
            float posY;
            Type type;
            std::string imagePath;
            b2Body *body;
    };

}

#endif // DRAWABLEOBJECTS_H
