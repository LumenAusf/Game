#pragma once

#ifndef SHADER_H
#define SHADER_H

//#include "enginecore.h"
//#include "texturefinal.h"

//#define GL_ERROR_CHECK()                                                          \
//    {                                                                             \
//        const unsigned int err = glGetError ();                                   \
//        if (err != GL_NO_ERROR)                                                   \
//        {                                                                         \
//            switch (err)                                                          \
//            {                                                                     \
//                case GL_INVALID_ENUM:                                             \
//                    std::cerr << "GL_INVALID_ENUM" << std::endl;                  \
//                    break;                                                        \
//                case GL_INVALID_VALUE:                                            \
//                    std::cerr << "GL_INVALID_VALUE" << std::endl;                 \
//                    break;                                                        \
//                case GL_INVALID_OPERATION:                                        \
//                    std::cerr << "GL_INVALID_OPERATION" << std::endl;             \
//                    break;                                                        \
//                case GL_INVALID_FRAMEBUFFER_OPERATION:                            \
//                    std::cerr << "GL_INVALID_FRAMEBUFFER_OPERATION" << std::endl; \
//                    break;                                                        \
//                case GL_OUT_OF_MEMORY:                                            \
//                    std::cerr << "GL_OUT_OF_MEMORY" << std::endl;                 \
//                    break;                                                        \
//            }                                                                     \
//            assert (false);                                                       \
//        }                                                                         \
//    }

// static PFNGLCREATESHADERPROC glCreateShader = nullptr;
// static PFNGLSHADERSOURCEARBPROC glShaderSource = nullptr;
// static PFNGLCOMPILESHADERARBPROC glCompileShader = nullptr;
// static PFNGLGETSHADERIVPROC glGetShaderiv = nullptr;
// static PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog = nullptr;
// static PFNGLDELETESHADERPROC glDeleteShader = nullptr;
// static PFNGLCREATEPROGRAMPROC glCreateProgram = nullptr;
// static PFNGLATTACHSHADERPROC glAttachShader = nullptr;
// static PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation = nullptr;
// static PFNGLLINKPROGRAMPROC glLinkProgram = nullptr;
// static PFNGLGETPROGRAMIVPROC glGetProgramiv = nullptr;
// static PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog = nullptr;
// static PFNGLDELETEPROGRAMPROC glDeleteProgram = nullptr;
// static PFNGLUSEPROGRAMPROC glUseProgram = nullptr;
// static PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation = nullptr;
// static PFNGLUNIFORM1IPROC glUniform1i = nullptr;
// static PFNGLACTIVETEXTUREPROC glActiveTexture_ = nullptr;
// static PFNGLUNIFORM4FVPROC glUniform4fv = nullptr;
// static PFNGLUNIFORMMATRIX3FVPROC glUniformMatrix3fv = nullptr;

namespace LumenAusf
{
    //    class texture_gl_es20;

    //    class shader_gl_es20
    //    {
    //       public:
    //        shader_gl_es20 (std::string_view vertex_src, std::string_view fragment_src, const std::vector<std::tuple<GLuint, const GLchar*>>&
    //        attributes);
    //        void use () const;
    //        void set_uniform (std::string_view uniform_name, texture_gl_es20* texture);
    //        void set_uniform (std::string_view uniform_name, const Color& c);
    //        void set_uniform (std::string_view uniform_name, const mat2x3& m);

    //       private:
    //        GLuint compile_shader (GLenum shader_type, std::string_view src);
    //        GLuint link_shader_program (const std::vector<std::tuple<GLuint, const GLchar*>>& attributes);

    //        GLuint vert_shader = 0;
    //        GLuint frag_shader = 0;
    //        GLuint program_id = 0;
    //    };
}

#endif    // SHADER_H
