#include "texturefinal.h"
#include "enginecore.h"

namespace LumenAusf
{
    texture_gl_es20::texture_gl_es20 (std::string_view path, int countH, int countW) : file_path (path)
    {
        countOnH = countH;
        countOnW = countW;

        std::vector<unsigned char> png_file_in_memory;
        std::ifstream ifs (path.data (), std::ios_base::binary);
        if (!ifs)
        {
            throw std::runtime_error ("can't load texture");
        }
        ifs.seekg (0, std::ios_base::end);
        std::streamoff pos_in_file = ifs.tellg ();
        png_file_in_memory.resize (static_cast<size_t> (pos_in_file));
        ifs.seekg (0, std::ios_base::beg);
        if (!ifs)
        {
            throw std::runtime_error ("can't load texture");
        }

        ifs.read (reinterpret_cast<char*> (png_file_in_memory.data ()), pos_in_file);
        if (!ifs.good ())
        {
            throw std::runtime_error ("can't load texture");
        }

        std::vector<unsigned char> image;
        unsigned long w = 0;
        unsigned long h = 0;
        int error = decodePNG (image, w, h, &png_file_in_memory[0], png_file_in_memory.size ());

        std::vector<unsigned char> revertimage;
        for (ulong i = h - 1; i < h; i--)
        {
            for (ulong j = 0; j < w * 4; j++)
            {
                revertimage.push_back (image.at (i * w * 4 + j));
            }
        }
        image = revertimage;

        // if there's an error, display it
        if (error != 0)
        {
            std::cerr << "error: " << error << std::endl;
            throw std::runtime_error ("can't load texture");
        }

        glGenTextures (1, &tex_handl);
        GL_ERROR_CHECK ();
        glBindTexture (GL_TEXTURE_2D, tex_handl);
        GL_ERROR_CHECK ();

        GLint mipmap_level = 0;
        GLint border = 0;
        GLsizei width = static_cast<GLsizei> (w);
        GLsizei height = static_cast<GLsizei> (h);
        glTexImage2D (GL_TEXTURE_2D, mipmap_level, GL_RGBA, width, height, border, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);
        GL_ERROR_CHECK ();

        glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        GL_ERROR_CHECK ();
        glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        GL_ERROR_CHECK ();
    }

    texture_gl_es20::~texture_gl_es20 ()
    {
        glDeleteTextures (1, &tex_handl);
        GL_ERROR_CHECK ();
    }
}
