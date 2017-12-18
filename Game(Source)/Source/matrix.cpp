#include "matrix.h"

namespace LumenAusf
{
    mat2x3::mat2x3 () : col0 (1.0f, 0.f), col1 (0.f, 1.f), delta (0.f, 0.f) {}

    mat2x3 mat2x3::identity () { return mat2x3::scale (1.f); }

    mat2x3 mat2x3::scale (float scale)
    {
        mat2x3 result;
        result.col0.x = scale;
        result.col1.y = scale;
        return result;
    }

    mat2x3 mat2x3::rotation (float angle)
    {
        mat2x3 result;

        result.col0.x = std::cos (angle);
        result.col0.y = std::sin (angle);

        result.col1.x = -std::sin (angle);
        result.col1.y = std::cos (angle);

        return result;
    }

    mat2x3 mat2x3::move (const vec2& delta)
    {
        mat2x3 r = mat2x3::identity ();
        r.delta = delta;
        return r;
    }

    mat2x3 operator* (const mat2x3& m1, const mat2x3& m2)
    {
        mat2x3 r;

        r.col0.x = m1.col0.x * m2.col0.x + m1.col1.x * m2.col0.y;
        r.col1.x = m1.col0.x * m2.col1.x + m1.col1.x * m2.col1.y;
        r.col0.y = m1.col0.y * m2.col0.x + m1.col1.y * m2.col0.y;
        r.col1.y = m1.col0.y * m2.col1.x + m1.col1.y * m2.col1.y;

        r.delta.x = m1.delta.x * m2.col0.x + m1.delta.y * m2.col0.y + m2.delta.x;
        r.delta.y = m1.delta.x * m2.col1.x + m1.delta.y * m2.col1.y + m2.delta.y;

        return r;
    }

    std::istream& operator>> (std::istream& is, mat2x3& m)
    {
        is >> m.col0.x;
        is >> m.col1.x;
        is >> m.col0.y;
        is >> m.col1.y;
        return is;
    }

    vec2 operator* (const vec2& v, const mat2x3& m)
    {
        vec2 result;
        result.x = v.x * m.col0.x + v.y * m.col0.y + m.delta.x;
        result.y = v.x * m.col1.x + v.y * m.col1.y + m.delta.y;
        return result;
    }
}
