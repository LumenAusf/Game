#include "color.h"

namespace LumenAusf
{
    std::istream& operator>> (std::istream& is, Color& c)
    {
        float r = 0.f;
        float g = 0.f;
        float b = 0.f;
        float a = 0.f;
        is >> r;
        is >> g;
        is >> b;
        is >> a;
        c = Color (r, g, b, a);
        return is;
    }

    // todo: transfer to .cpp

    Color::Color (std::uint32_t rgba_) : rgba (rgba_) {}

    Color::Color (float r, float g, float b, float a)
    {
        assert (r <= 1 && r >= 0);
        assert (g <= 1 && g >= 0);
        assert (b <= 1 && b >= 0);
        assert (a <= 1 && a >= 0);

        std::uint32_t r_ = static_cast<std::uint32_t> (r * 255);
        std::uint32_t g_ = static_cast<std::uint32_t> (g * 255);
        std::uint32_t b_ = static_cast<std::uint32_t> (b * 255);
        std::uint32_t a_ = static_cast<std::uint32_t> (a * 255);

        rgba = a_ << 24 | b_ << 16 | g_ << 8 | r_;
    }

    float Color::get_r () const
    {
        std::uint32_t r_ = (rgba & 0x000000FF) >> 0;
        return r_ / 255.f;
    }

    float Color::get_g () const
    {
        std::uint32_t g_ = (rgba & 0x0000FF00) >> 8;
        return g_ / 255.f;
    }

    float Color::get_b () const
    {
        std::uint32_t b_ = (rgba & 0x00FF0000) >> 16;
        return b_ / 255.f;
    }

    float Color::get_a () const
    {
        std::uint32_t a_ = (rgba & 0xFF000000) >> 24;
        return a_ / 255.f;
    }

    void Color::set_r (const float r)
    {
        std::uint32_t r_ = static_cast<std::uint32_t> (r * 255);
        rgba &= 0xFFFFFF00;
        rgba |= (r_ << 0);
    }

    void Color::set_g (const float g)
    {
        std::uint32_t g_ = static_cast<std::uint32_t> (g * 255);
        rgba &= 0xFFFF00FF;
        rgba |= (g_ << 8);
    }

    void Color::set_b (const float b)
    {
        std::uint32_t b_ = static_cast<std::uint32_t> (b * 255);
        rgba &= 0xFF00FFFF;
        rgba |= (b_ << 16);
    }

    void Color::set_a (const float a)
    {
        std::uint32_t a_ = static_cast<std::uint32_t> (a * 255);
        rgba &= 0x00FFFFFF;
        rgba |= a_ << 24;
    }
}
