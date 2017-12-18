#pragma once

#ifndef COLOR_H
#define COLOR_H

#include <cassert>
#include <cstdint>
#include <iostream>

namespace LumenAusf
{
    class Color
    {
       public:
        Color () = default;
        explicit Color (std::uint32_t rgba_);
        Color (float r, float g, float b, float a);

        float get_r () const;
        float get_g () const;
        float get_b () const;
        float get_a () const;

        void set_r (const float r);
        void set_g (const float g);
        void set_b (const float b);
        void set_a (const float a);

       private:
        std::uint32_t rgba = 0;
    };

    std::istream& operator>> (std::istream& is, Color& c);
}
#endif    // COLOR_H
