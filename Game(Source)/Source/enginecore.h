#pragma once

#ifndef ENGINECORE_H
#define ENGINECORE_H

#include "engine.h"
#include "picopng.hxx"
#include "shader.h"
#include "texture.h"
#include "texturefinal.h"

// PFNGLCREATESHADERPROC glCreateShader = nullptr;
// PFNGLSHADERSOURCEARBPROC glShaderSource = nullptr;
// PFNGLCOMPILESHADERARBPROC glCompileShader = nullptr;
// PFNGLGETSHADERIVPROC glGetShaderiv = nullptr;
// PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog = nullptr;
// PFNGLDELETESHADERPROC glDeleteShader = nullptr;
// PFNGLCREATEPROGRAMPROC glCreateProgram = nullptr;
// PFNGLATTACHSHADERPROC glAttachShader = nullptr;
// PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation = nullptr;
// PFNGLLINKPROGRAMPROC glLinkProgram = nullptr;
// PFNGLGETPROGRAMIVPROC glGetProgramiv = nullptr;
// PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog = nullptr;
// PFNGLDELETEPROGRAMPROC glDeleteProgram = nullptr;
// PFNGLUSEPROGRAMPROC glUseProgram = nullptr;
// PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation = nullptr;
// PFNGLUNIFORM1IPROC glUniform1i = nullptr;
// PFNGLACTIVETEXTUREPROC glActiveTexture_ = nullptr;
// PFNGLUNIFORM4FVPROC
//    glUniform4fv
//        = nullptr;
//        PFNGLUNIFORMMATRIX3FVPROC glUniformMatrix3fv = nullptr;

//        PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer = nullptr;
//        PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray = nullptr;
//        PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray = nullptr;
namespace LumenAusf
{
    class Glfunc
    {
       public:
        PFNGLCREATESHADERPROC glCreateShader;
        PFNGLSHADERSOURCEARBPROC glShaderSource;
        PFNGLCOMPILESHADERARBPROC glCompileShader;
        PFNGLGETSHADERIVPROC glGetShaderiv;
        PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
        PFNGLDELETESHADERPROC glDeleteShader;
        PFNGLCREATEPROGRAMPROC glCreateProgram;
        PFNGLATTACHSHADERPROC glAttachShader;
        PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation;
        PFNGLLINKPROGRAMPROC glLinkProgram;
        PFNGLGETPROGRAMIVPROC glGetProgramiv;
        PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
        PFNGLDELETEPROGRAMPROC glDeleteProgram;
        PFNGLUSEPROGRAMPROC glUseProgram;
        PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
        PFNGLUNIFORM1IPROC glUniform1i;
        PFNGLACTIVETEXTUREPROC glActiveTexture_;
        PFNGLUNIFORM4FVPROC
            glUniform4fv
                ;
                PFNGLUNIFORMMATRIX3FVPROC glUniformMatrix3fv;
                PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
                PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
                PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;

                static Glfunc* Get ()
                {
                    if (ptr == nullptr)
                        ptr = new Glfunc ();
                    return ptr;
                }

                static Glfunc* ptr;
    };
}

// extern PFNGLCREATESHADERPROC glCreateShader;
// extern PFNGLSHADERSOURCEARBPROC glShaderSource;
// extern PFNGLCOMPILESHADERARBPROC glCompileShader;
// extern PFNGLGETSHADERIVPROC glGetShaderiv;
// extern PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
// extern PFNGLDELETESHADERPROC glDeleteShader;
// extern PFNGLCREATEPROGRAMPROC glCreateProgram;
// extern PFNGLATTACHSHADERPROC glAttachShader;
// extern PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation;
// extern PFNGLLINKPROGRAMPROC glLinkProgram;
// extern PFNGLGETPROGRAMIVPROC glGetProgramiv;
// extern PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
// extern PFNGLDELETEPROGRAMPROC glDeleteProgram;
// extern PFNGLUSEPROGRAMPROC glUseProgram;
// extern PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
// extern PFNGLUNIFORM1IPROC glUniform1i;
// extern PFNGLACTIVETEXTUREPROC GlActiveTexture_;
// extern PFNGLACTIVETEXTUREPROC glActiveTexture_{std::get({if (GlActiveTexture_ == nullptr) return load_gl_func});
// extern PFNGLUNIFORM4FVPROC glUniform4fv;
// extern PFNGLUNIFORMMATRIX3FVPROC glUniformMatrix3fv;
// extern PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
// extern PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
// extern PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;

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

// we have to load all extension GL function pointers
// dynamically from OpenGL library
// so first declare function pointers for all we need

template <typename T>
static void load_gl_func (const char* func_name, T& result)
{
    void* gl_pointer = SDL_GL_GetProcAddress (func_name);
    if (nullptr == gl_pointer)
    {
        throw std::runtime_error (std::string ("can't load GL function") + func_name);
    }
    result = reinterpret_cast<T> (gl_pointer);
}

namespace LumenAusf
{
    //    class texture_gl_es20 final : public Texture
    //    {
    //       public:
    //        explicit texture_gl_es20 (std::string_view path);
    //        ~texture_gl_es20 () override;

    //        void bind () const
    //        {
    //            glBindTexture (GL_TEXTURE_2D, tex_handl);
    //            GL_ERROR_CHECK ();
    //        }

    //        std::uint32_t get_width () const final { return width; }
    //        std::uint32_t get_height () const final { return height; }

    //       private:
    //        std::string file_path;
    //        GLuint tex_handl = 0;
    //        std::uint32_t width = 0;
    //        std::uint32_t height = 0;
    //    };

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

    class shader_gl_es20;

    class EngineCore
    {
       public:
        EngineCore ();
        ~EngineCore ();

        void Init (bool versionCritical, int width, int height, std::string windowName);
        bool InitGl ();
        bool CheckVersion ();
        void ReadEvent (Engine* engine);
        void Finish ();
        Texture* CreateTexture (std::string_view path, int hCount = 1, int wCount = 1);
        void DestroyTexture (Texture* t);
        //        bool DrawTriangle (const triangle& t);
        void DrawTriangle (const tri0& t, const Color& c);
        void DrawTriangle (const tri1& t);
        void DrawTriangle (const tri2& t, Texture* tex);
        void DrawTriangle (const tri2& t, Texture* tex, const mat2x3& m);
        void Clear ();
        bool LoadTexture (std::string path);
        void SwapBuffers ();
        float getTimeFromInit ();

        SDL_Window* window;
        shader_gl_es20* shader00 = nullptr;
        shader_gl_es20* shader01 = nullptr;
        shader_gl_es20* shader02 = nullptr;
        shader_gl_es20* shader03 = nullptr;
        static EngineCore* EnCore;
    };
}
#endif    // ENGINECORE_H
