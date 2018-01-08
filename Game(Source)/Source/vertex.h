#pragma once

#ifndef VERTEX_H
#define VERTEX_H

#include "color.h"
//#include "vec2.h"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace LumenAusf
{
    /// vertex with position only
    struct vertexP
    {
        glm::vec3 pos;
    };

    /// vertex with position and texture coordinate
    struct vertexPC
    {
        glm::vec3 pos;
        Color c;
    };

    /// vertex position + color + texture coordinate
    struct vertexPTC
    {
        glm::vec3 pos;
        glm::vec2 uv;
        Color c;
    };

    std::istream& operator>> (std::istream& is, vertexP& v);

    std::istream& operator>> (std::istream& is, vertexPC& v);

    std::istream& operator>> (std::istream& is, vertexPTC& v);

    //    v0 Lerp (const LumenAusf::v0& vl, const LumenAusf::v0& vr, const float a);
}
#endif    // VERTEX_H
