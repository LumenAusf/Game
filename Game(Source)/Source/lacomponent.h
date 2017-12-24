#pragma once

#ifndef LACOMPONENT_H
#define LACOMPONENT_H

#include "gameobject.h"

namespace LumenAusf
{
    class GameObject;

    class LAComponent
    {
       public:
        LAComponent () {}
        virtual ~LAComponent () {}
        virtual void Awake () {}
        virtual void Start () {}
        virtual void Update () {}
        virtual void onEnable () {}
        virtual void onDisable () {}

        bool getEnabled () const;
        void setEnabled (bool value);
        GameObject* getGameObject () const;
        void setGameObject (GameObject* value);

       private:
        bool enabled = true;
        GameObject* gameObject = nullptr;
    };
}

#endif    // LACOMPONENT_H
