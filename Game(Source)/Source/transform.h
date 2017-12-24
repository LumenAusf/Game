#pragma once

#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "gameobject.h"
#include "matrix.h"

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
        void SetPosition (vec2 pos) { localPosition = mat2x3::identity () * mat2x3::move (pos); }

       private:
    };
}
#endif    // TRANSFORM_H
