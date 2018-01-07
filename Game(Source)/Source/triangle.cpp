#include "triangle.h"

namespace LumenAusf
{
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

    //    tri2::tri2(const tri2&newT)
    //    {
    //        v[0] = newT.v[0];
    //        v[1] = newT.v[1];
    //        v[2] = newT.v[2];
    //    }

    tri0 Lerp (const tri0& tl, const tri0& tr, const float a)
    {
        tri0 r;
        r.v[0] = Lerp (tl.v[0], tr.v[0], a);
        r.v[1] = Lerp (tl.v[1], tr.v[1], a);
        r.v[2] = Lerp (tl.v[2], tr.v[2], a);
        return r;
    }
}
