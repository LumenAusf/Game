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

    vec2 operator+ (const vec2& l, const vec2& r)
    {
        vec2 result;
        result.x = l.x + r.x;
        result.y = l.y + r.y;
        return result;
    }

    std::istream& operator>> (std::istream& is, vec2& v)
    {
        is >> v.x;
        is >> v.y;
        return is;
    }

    // todo: transfer to .cpp
    vec2::vec2 () : x (0.f), y (0.f) {}
    vec2::vec2 (float x_, float y_) : x (x_), y (y_) {}
}
#endif    // VEC2_H
