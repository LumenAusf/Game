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
        static bool CanSetSo (std::vector<trianglePTC> array_1, glm::mat4 first, std::vector<trianglePTC> array_2, glm::mat4 second);

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
