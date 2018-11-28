#include <tuple>

#ifndef DRAWABLEOBJECTS_H
#define DRAWABLEOBJECTS_H

#endif // DRAWABLEOBJECTS_H

namespace DrawableObjects
{
    using posTuple = std::tuple<unsigned int, unsigned int>;

    enum class Type
    {
        projectile,
        enemy,
        player
    };


    class DrawableObject
    {
    public:
        DrawableObject(posTuple pos)
        {
            posX = std::get<0>(pos);
            posY = std::get<1>(pos);
        }

        posTuple getPos()
        {
            return std::make_tuple(posX, posY);
        }

        void updatePosX(unsigned int x) { posX = x; }
        void updatePosY(unsigned int y) { posY = y; }

    private:
        unsigned int posX;
        unsigned int posY;
        Type type;
    };


    class Player : public DrawableObject
    {
        //
    };


    class Enemy : public DrawableObject
    {
        //
    };


    class Projectile : public DrawableObject
    {
        //
    };

}
