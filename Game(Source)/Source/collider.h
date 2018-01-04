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
        static bool CanSetSo (std::vector<tri2> array_1, mat2x3 first, std::vector<tri2> array_2, mat2x3 second);

        virtual ~Collider ();

        // Component interface
       public:
        void Awake ();
        void Start ();
        void onEnable ();
        void onDisable ();
        void onDestroy ();

        // Component interface
       public:
        void Destroy ();
    };
}

#endif    // COLLIDER_H
