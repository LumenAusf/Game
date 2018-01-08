#pragma once

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <list>
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

        glm::mat4 GetGlobalMatrix () { return getGlobalPosition () * getGlobalRotation () * getGlobalScale (); }
        glm::mat4 GetLocalMatrix () { return getLocalPosition () * getLocalRotation () * getLocalScale (); }
        void SetPosition (glm::vec3 pos) { position = glm::translate (glm::mat4 (), pos); }

        glm::mat4 getLocalScale () const;
        void setLocalScale (const glm::mat4& value);

        glm::mat4 getLocalRotation () const;
        void setLocalRotation (const glm::mat4& value);

        glm::mat4 getLocalPosition () const;
        void setLocalPosition (const glm::mat4& value);

        glm::mat4 getGlobalScale () const;
        //        void setGlobalScale (const mat2x3& value);

        glm::mat4 getGlobalRotation () const;
        //        void setGlobalRotation (const mat2x3& value);

        glm::mat4 getGlobalPosition () const;
        //        void setGlobalPosition (const mat2x3& value);

        glm::mat4 getAspect () const;
        void setAspect (const glm::mat4& value);

       private:
        glm::mat4 position;
        glm::mat4 rotation;
        glm::mat4 scale;
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
        void virtual Destroy () {}

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

        GameObject (std::string name = "");
        GameObject (Transform* parent, std::string name = "");
        ~GameObject ();

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
                if (components.size () < i)
                    continue;
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
        static void RenderAll ();
        void OnDestroy ();
        bool CanMove (glm::vec3 pos);

        static std::vector<GameObject*> objects;
    };
}
#endif    // GAMEOBJECT_H
