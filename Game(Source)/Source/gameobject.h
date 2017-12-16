#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include "texture.h"
#include "transform.h"
#include "triangle.h"

namespace LumenAusf
{
    enum Arrows
    {
        Up,
        Right,
        Down,
        Left
    };

    class GameObject
    {
       public:
        Arrows arrows;
        Texture* texture;
        Transform transform;
        std::vector<tri2> triangles;
        GameObject () {}
        GameObject (Transform a, std::vector<tri2> b, Texture* c)
        {
            transform = a;
            triangles = b;
            texture = c;
        }

       private:
    };
}
#endif    // GAMEOBJECT_H
