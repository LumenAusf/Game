#pragma once

#ifndef COLLIDER_H
#define COLLIDER_H

#include "gameobject.h"
#include "meshrenderer.h"

namespace LumenAusf
{
    class Component;

    class Collider : public Component
    {
       public:
        Collider (GameObject* owner);
        static bool IsColided (GameObject* first, GameObject* second);

        virtual ~Collider ();

        // Component interface
       public:
        void Awake ();
        void Start ();
        void onEnable ();
        void onDisable ();
        void onDestroy ();
    };
}

#endif    // COLLIDER_H
