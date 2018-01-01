#pragma once

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <algorithm>
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
        GameObject* gameObject = nullptr;
        Transform* parent = nullptr;
        std::vector<Transform*> children;

        mat2x3 GetGlobalMatrix () { return getGlobalScale () * getGlobalRotation () * getGlobalPosition () * aspect; }
        mat2x3 GetLocalMatrix () { return getLocalScale () * getLocalRotation () * getLocalPosition () * aspect; }
        void SetPosition (vec2 pos) { setLocalPosition (mat2x3 () * mat2x3::move (pos)); }

        mat2x3 getLocalScale () const;
        void setLocalScale (const mat2x3& value);

        mat2x3 getLocalRotation () const;
        void setLocalRotation (const mat2x3& value);

        mat2x3 getLocalPosition () const;
        void setLocalPosition (const mat2x3& value);

        mat2x3 getGlobalScale () const;
        //        void setGlobalScale (const mat2x3& value);

        mat2x3 getGlobalRotation () const;
        //        void setGlobalRotation (const mat2x3& value);

        mat2x3 getGlobalPosition () const;
        //        void setGlobalPosition (const mat2x3& value);

        mat2x3 getAspect () const;
        void setAspect (const mat2x3& value);

       private:
        mat2x3 localScale;
        mat2x3 localRotation;
        mat2x3 localPosition;
        mat2x3 globalScale;
        mat2x3 globalRotation;
        mat2x3 globalPosition;
        mat2x3 aspect;
    };

    class Component
    {
       public:
        Component (GameObject* owner) { gameObject = owner; }
        void virtual Awake () {}
        void virtual Start () {}
        void virtual Update () {}
        void virtual onEnable () {}
        void virtual onDisable () {}
        void virtual onDestroy () {}

        bool getEnabled () const { return enabled; }
        void setEnabled (bool value)
        {
            enabled = value;
            value ? onEnable () : onDisable ();
        }
        GameObject* getGameObject () const { return gameObject; }

       protected:
        GameObject* gameObject = nullptr;
        bool enabled = true;
    };

    class GameObject
    {
       public:
        Transform* transform;
        std::vector<Component*> components;
        bool enabled = true;
        std::string name = "GameObject";
        std::string tag = "";

        GameObject (std::string name = "")
        {
            transform = new Transform ();
            transform->parent = nullptr;
            objects.push_back (this);
            this->name = name != "" ? name : this->name;
        }
        GameObject (Transform* parent, std::string name = "")
        {
            transform = new Transform ();
            transform->parent = parent;
            if (parent != nullptr)
                parent->children.push_back (transform);
            objects.push_back (this);
            this->name = name != "" ? name : this->name;
        }
        ~GameObject ()
        {
            auto a = std::find (objects.cbegin (), objects.cend (), this);
            objects.erase (a);
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
            auto a = new T (this);
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

        static void UpdateAll ();
        static void AwakeAll ();
        static void StartAll ();
        static void FixedUpdateAll ();

       private:
        static std::vector<GameObject*> objects;
    };
}
#endif    // GAMEOBJECT_H
