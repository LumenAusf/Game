#ifndef TEXTURE_H
#define TEXTURE_H

#include <cstdint>

namespace LumenAusf
{
    class Texture
    {
       public:
        virtual ~Texture ();
        virtual std::uint32_t get_width () const = 0;
        virtual std::uint32_t get_height () const = 0;
    };

    // todo: transfer to .cpp

    Texture::~Texture () {}
}
#endif    // TEXTURE_H
