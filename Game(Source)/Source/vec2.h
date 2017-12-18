#pragma once

#ifndef VEC2_H
#define VEC2_H

#include <sstream>

namespace LumenAusf
{
    /* Structure for storing two variables (x and y) of the float type */
    struct vec2
    {
        vec2 ();
        vec2 (float x, float y);
        float x = 0;
        float y = 0;
    };

    vec2 operator+ (const vec2& l, const vec2& r);

    std::istream& operator>> (std::istream& is, vec2& v);
}
#endif    // VEC2_H
