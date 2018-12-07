#ifndef DRAWABLEOBJECTS_H
#define DRAWABLEOBJECTS_H

#include <QImage>
#include <tuple>
#include <string>
#include <Box2D/Box2D.h>
#include <QDebug>

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
        static int ID;
            GameObject(posTuple pos)
            {
                this->posX = std::get<0>(pos);
                this->posY = std::get<1>(pos);
                this->body = nullptr;
                ID++;
                qInfo() << "ID is " << ID;
            }

            GameObject(posTuple pos, b2Body &body)
            {
                this->posX = std::get<0>(pos);
                this->posY = std::get<1>(pos);
                this->body = &body;
                ID++;
                qInfo() << "ID is " << ID;
            }

//            ~GameObject()
//            {

//            }

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
                    case Type::targetedEnemy : return "targeted enemy";
                    case Type::player        : return "player";
                    case Type::explosion     : return "explosion";
                }
            }

            b2Body& getBody() { return *body; }

        private:
            // Sets the values of the x,y positions to the latest b2Body positions
            void updatePos() {
                posX = body->GetPosition().x;
                posY = -body->GetPosition().y;
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
