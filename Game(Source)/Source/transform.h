#pragma once

#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "matrix.h"

namespace LumenAusf
{
    class Transform
    {
       public:
        mat2x3 scale;
        mat2x3 rotation;
        mat2x3 position;
        mat2x3 aspect;

        mat2x3 GetMatrix () { return scale * rotation * position * aspect; }

       private:
    };
}
#endif    // TRANSFORM_H
