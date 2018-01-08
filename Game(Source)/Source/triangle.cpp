#include "triangle.h"

namespace LumenAusf
{
    std::istream& operator>> (std::istream& is, triangleP& t)
    {
        is >> t.v[0];
        is >> t.v[1];
        is >> t.v[2];
        return is;
    }

    std::istream& operator>> (std::istream& is, trianglePC& t)
    {
        is >> t.v[0];
        is >> t.v[1];
        is >> t.v[2];
        return is;
    }

    std::istream& operator>> (std::istream& is, trianglePTC& t)
    {
        is >> t.v[0];
        is >> t.v[1];
        is >> t.v[2];
        return is;
    }

    // todo: transfer to .cpp

    triangleP::triangleP () : v{vertexP (), vertexP (), vertexP ()} {}

    trianglePC::trianglePC () : v{vertexPC (), vertexPC (), vertexPC ()} {}

    trianglePTC::trianglePTC () : v{vertexPTC (), vertexPTC (), vertexPTC ()} {}

    //    tri2::tri2(const tri2&newT)
    //    {
    //        v[0] = newT.v[0];
    //        v[1] = newT.v[1];
    //        v[2] = newT.v[2];
    //    }

    //    triangleP Lerp (const triangleP& tl, const triangleP& tr, const float a)
    //    {
    //        triangleP r;
    //        r.v[0] = Lerp (tl.v[0], tr.v[0], a);
    //        r.v[1] = Lerp (tl.v[1], tr.v[1], a);
    //        r.v[2] = Lerp (tl.v[2], tr.v[2], a);
    //        return r;
    //    }
}
