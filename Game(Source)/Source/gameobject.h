#pragma once

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include "lacomponent.h"
#include "texture.h"
#include "transform.h"
#include "triangle.h"

enum Arrows
{
    Up,
    Right,
    Down,
    Left
};

namespace LumenAusf
{
    class LAComponent;

    class GameObject
    {
       public:
        Transform* transform;
        std::vector<LAComponent*> components;
        bool enabled;
        std::string name;

        GameObject () { transform = new Transform (); }
        GameObject (Transform* parent)
        {
            transform = new Transform ();
            transform->parent = parent;
            parent->children.push_back (transform);
        }

        LAComponent* AddComponent (LAComponent* component);
        LAComponent* GetOrAddComponent (LAComponent* component);
        LAComponent* GetComponent (LAComponent* component);
        void RemoveComponent (LAComponent* component);

        //        //        Arrows arrows;
        //        Texture* texture = nullptr;
        ////        Transform transform;
        //        std::vector<tri2> triangles;
        //        std::vector<tri2> trianglesOriginals;
        //        vec2 elementCountXY, usefromTo;
        //        bool isAtlas;
        //        int startId, finishId;
        //        int sizeAtlasItem;
        //        int currentAtlasItem;
        //        GameObject () {}
        //        GameObject (Transform * a, std::vector<tri2> b)
        //        {
        //            transform = a;
        //            triangles = b;
        //            trianglesOriginals = b;
        //        }
        //        void SetAtlas (Texture* texture, vec2 elementCountXY, vec2 UsefromTo);
        //        void SetTexture (Texture* texture);
        //        void Next ();
        //        void SetPosition (vec2 position);

       private:
    };
}
#endif    // GAMEOBJECT_H
