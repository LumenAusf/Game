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
        v2 v[3];
    };

    std::istream& operator>> (std::istream& is, tri0& t)
    {
        is >> t.v[0];
        is >> t.v[1];
        is >> t.v[2];
        return is;
    }

    std::istream& operator>> (std::istream& is, tri1& t)
    {
        is >> t.v[0];
        is >> t.v[1];
        is >> t.v[2];
        return is;
    }

    std::istream& operator>> (std::istream& is, tri2& t)
    {
        is >> t.v[0];
        is >> t.v[1];
        is >> t.v[2];
        return is;
    }

    // todo: transfer to .cpp

    tri0::tri0 () : v{v0 (), v0 (), v0 ()} {}

    tri1::tri1 () : v{v1 (), v1 (), v1 ()} {}

    tri2::tri2 () : v{v2 (), v2 (), v2 ()} {}

    LumenAusf::tri0 Lerp (const LumenAusf::tri0& tl, const LumenAusf::tri0& tr, const float a)
    {
        LumenAusf::tri0 r;
        r.v[0] = Lerp (tl.v[0], tr.v[0], a);
        r.v[1] = Lerp (tl.v[1], tr.v[1], a);
        r.v[2] = Lerp (tl.v[2], tr.v[2], a);
        return r;
    }
}
#endif    // TRIANGLE_H
