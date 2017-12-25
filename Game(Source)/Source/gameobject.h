#pragma once

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
#include <vector>
#include "matrix.h"
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
    class GameObject;

    class Transform
    {
       public:
        mat2x3 localScale;
        mat2x3 localRotation;
        mat2x3 localPosition;
        mat2x3 globalScale;
        mat2x3 globalRotation;
        mat2x3 globalPosition;
        mat2x3 aspect;
        GameObject* gameObject = nullptr;
        Transform* parent = nullptr;
        std::vector<Transform*> children;

        mat2x3 GetGlobalMatrix () { return globalScale * globalRotation * globalPosition * aspect; }
        mat2x3 GetLocalMatrix () { return localScale * localRotation * localPosition * aspect; }
        void SetPosition (vec2 pos) { globalPosition = mat2x3 () * mat2x3::move (pos); }

       private:
    };

    class Component
    {
       public:
        void Awake () {}
        void Start () {}
        void Update () {}
        void onEnable () {}
        void onDisable () {}

        //         bool getEnabled () const ;
        //         void setEnabled (bool value) ;
        //         GameObject* getGameObject () const ;
        //         void setGameObject (GameObject* value) ;

       protected:
    };

    class GameObject
    {
       public:
        Transform* transform;
        std::vector<Component*> components;
        bool enabled;
        std::string name;

        GameObject () { transform = new Transform (); }
        GameObject (Transform* parent)
        {
            transform = new Transform ();
            transform->parent = parent;
            if (parent != nullptr)
                parent->children.push_back (transform);
        }

        Component* AddComponent (Component* component);
        Component* GetOrAddComponent (Component* component);
        Component* GetComponent (Component* component);
        void RemoveComponent (Component* component);

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
