#pragma once

#ifndef VERTEX_H
#define VERTEX_H

#include "color.h"
#include "vec2.h"

namespace LumenAusf
{
    /// vertex with position only
    struct v0
    {
        vec2 pos;
    };

    /// vertex with position and texture coordinate
    struct v1
    {
        vec2 pos;
        Color c;
    };

    /// vertex position + color + texture coordinate
    struct v2
    {
        vec2 pos;
        vec2 uv;
        Color c;
    };

    std::istream& operator>> (std::istream& is, v0& v);

    std::istream& operator>> (std::istream& is, v1& v);

    std::istream& operator>> (std::istream& is, v2& v);

    v0 Lerp (const LumenAusf::v0& vl, const LumenAusf::v0& vr, const float a);
}
#endif    // VERTEX_H
