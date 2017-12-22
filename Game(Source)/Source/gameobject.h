#pragma once

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
        Texture* texture = nullptr;
        Transform transform;
        std::vector<tri2> triangles;
        std::vector<tri2> trianglesOriginals;
        vec2 elementCountXY, usefromTo;
        bool isAtlas;
        int startId, finishId;
        int sizeAtlasItem;
        int currentAtlasItem;
        GameObject () {}
        GameObject (Transform a, std::vector<tri2> b)
        {
            transform = a;
            triangles = b;
            trianglesOriginals = b;
        }
        void SetAtlas (Texture* texture, vec2 elementCountXY, vec2 UsefromTo);
        void SetTexture (Texture* texture);
        void Next ();
        //        {
        //            for (unsigned long i = 0; i < triangles.size (); i++)
        //            {
        //                for (int j = 0; j < 3; j++)
        //                {
        //                    triangles.at (i).v[j].uv.x *= (float(sizeAtlasItem) / texture->get_width ());
        //                    triangles.at (i).v[j].uv.x += (float(sizeAtlasItem) / texture->get_width ());
        //                    triangles.at (i).v[j].uv.y *= (float(sizeAtlasItem) / texture->get_height ());
        //                    triangles.at (i).v[j].uv.y -= (float(sizeAtlasItem) / texture->get_height ());
        //                }
        //            }
        //        }

       private:
    };
}
#endif    // GAMEOBJECT_H
