#pragma once

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "vertex.h"

namespace LumenAusf
{
    /// triangle with positions
    struct triangleP
    {
        triangleP ();
        vertexP v[3];
    };

    /// triangle with positions and color
    struct trianglePC
    {
        trianglePC ();
        vertexPC v[3];
    };

    /// triangle with positions color and texture coordinate
    struct trianglePTC
    {
        trianglePTC ();
        vertexPTC v[3];
    };

    std::istream& operator>> (std::istream& is, triangleP& t);

    std::istream& operator>> (std::istream& is, trianglePC& t);

    std::istream& operator>> (std::istream& is, trianglePTC& t);

    //    tri0 Lerp (const tri0& tl, const tri0& tr, const float a);
}
#endif    // TRIANGLE_H
