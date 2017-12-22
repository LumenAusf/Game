#pragma once

#ifndef TEXTUREFINAL_H
#define TEXTUREFINAL_H

#include "enginecore.h"
#include "texture.h"

#define GL_ERROR_CHECK()                                                          \
    {                                                                             \
        const unsigned int err = glGetError ();                                   \
        if (err != GL_NO_ERROR)                                                   \
        {                                                                         \
            switch (err)                                                          \
            {                                                                     \
                case GL_INVALID_ENUM:                                             \
                    std::cerr << "GL_INVALID_ENUM" << std::endl;                  \
                    break;                                                        \
                case GL_INVALID_VALUE:                                            \
                    std::cerr << "GL_INVALID_VALUE" << std::endl;                 \
                    break;                                                        \
                case GL_INVALID_OPERATION:                                        \
                    std::cerr << "GL_INVALID_OPERATION" << std::endl;             \
                    break;                                                        \
                case GL_INVALID_FRAMEBUFFER_OPERATION:                            \
                    std::cerr << "GL_INVALID_FRAMEBUFFER_OPERATION" << std::endl; \
                    break;                                                        \
                case GL_OUT_OF_MEMORY:                                            \
                    std::cerr << "GL_OUT_OF_MEMORY" << std::endl;                 \
                    break;                                                        \
            }                                                                     \
            assert (false);                                                       \
        }                                                                         \
    }

namespace LumenAusf
{
    class texture_gl_es20 final : public Texture
    {
       public:
        explicit texture_gl_es20 (std::string_view path, int countH = 1, int countW = 1);
        ~texture_gl_es20 () override;

        void bind () const
        {
            glBindTexture (GL_TEXTURE_2D, tex_handl);
            GL_ERROR_CHECK ();
        }

        std::uint32_t get_width () const final { return width; }
        std::uint32_t get_height () const final { return height; }

       private:
        int countOnH = 1;
        int countOnW = 1;
        std::string file_path;
        GLuint tex_handl = 0;
        std::uint32_t width = 0;
        std::uint32_t height = 0;
    };
}

#endif    // TEXTUREFINAL_H
