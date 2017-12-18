#include "vertex.h"

namespace LumenAusf
{
    std::istream& operator>> (std::istream& is, v0& v)
    {
        is >> v.pos.x;
        is >> v.pos.y;

        return is;
    }

    std::istream& operator>> (std::istream& is, v1& v)
    {
        is >> v.pos.x;
        is >> v.pos.y;
        is >> v.c;
        return is;
    }

    std::istream& operator>> (std::istream& is, v2& v)
    {
        is >> v.pos.x;
        is >> v.pos.y;
        is >> v.uv;
        is >> v.c;
        return is;
    }

    // todo: transfer to .cpp

    v0 Lerp (const LumenAusf::v0& vl, const LumenAusf::v0& vr, const float a)
    {
        LumenAusf::v0 r;
        r.pos.x = (1.0f - a) * vl.pos.x + a * vr.pos.x;
        r.pos.y = (1.0f - a) * vl.pos.y + a * vr.pos.y;
        return r;
    }
}
