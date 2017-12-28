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
        void virtual Awake () {}
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

        template <typename T>
        typename std::enable_if<std::is_base_of<Component, T>::value, T*>::type AddComponent ()
        {
            bool Finded = false;
            for (size_t i = 0; i < components.size (); i++)
            {
                if (dynamic_cast<T*> (components.at (i)) != nullptr)
                {
                    Finded = true;
                    break;
                }
            }
            if (Finded)
            {
                throw new std::exception ();
            }
            auto a = new T ();
            components.push_back (a);
            return a;
        }

        template <typename T>
        typename std::enable_if<std::is_base_of<Component, T>::value, T*>::type GetOrAddComponent ()
        {
            auto temp = GetComponent<T> ();
            return temp == nullptr ? AddComponent<T> () : temp;
        }

        template <typename T>
        typename std::enable_if<std::is_base_of<Component, T>::value, T*>::type GetComponent ()
        {
            T* temp = nullptr;

            for (unsigned int i = 0; i < components.size (); i++)
            {
                temp = dynamic_cast<T*> (components.at (i));
                if (temp != nullptr)
                    break;
            }

            return temp;
        }

        template <typename T>
        typename std::enable_if<std::is_base_of<Component, T>::value, void>::type RemoveComponent ()
        {
            for (size_t i = 0; i < components.size (); i++)
            {
                if (dynamic_cast<T*> (components.at (i)) != nullptr)
                {
                    components.erase (components.cbegin () + static_cast<long> (i));
                    break;
                }
            }
        }

       private:
    };
}
#endif    // GAMEOBJECT_H
