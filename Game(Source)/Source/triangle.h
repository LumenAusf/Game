#pragma once

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "vertex.h"

namespace LumenAusf
{
    /// triangle with positions
    struct tri0
    {
        tri0 ();
        v0 v[3];
    };

    /// triangle with positions and color
    struct tri1
    {
        tri1 ();
        v1 v[3];
    };

    /// triangle with positions color and texture coordinate
    struct tri2
    {
        tri2 ();
        //        tri2(tri2 const &newT);
        v2 v[3];
    };

    std::istream& operator>> (std::istream& is, tri0& t);

    std::istream& operator>> (std::istream& is, tri1& t);

    std::istream& operator>> (std::istream& is, tri2& t);

    tri0 Lerp (const tri0& tl, const tri0& tr, const float a);
}
#endif    // TRIANGLE_H
