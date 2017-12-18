#include "enginecore.h"

namespace LumenAusf
{
    //    PFNGLCREATESHADERPROC glCreateShader = nullptr;
    //    PFNGLSHADERSOURCEARBPROC glShaderSource = nullptr;
    //    PFNGLCOMPILESHADERARBPROC glCompileShader = nullptr;
    //    PFNGLGETSHADERIVPROC glGetShaderiv = nullptr;
    //    PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog = nullptr;
    //    PFNGLDELETESHADERPROC glDeleteShader = nullptr;
    //    PFNGLCREATEPROGRAMPROC glCreateProgram = nullptr;
    //    PFNGLATTACHSHADERPROC glAttachShader = nullptr;
    //    PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation = nullptr;
    //    PFNGLLINKPROGRAMPROC glLinkProgram = nullptr;
    //    PFNGLGETPROGRAMIVPROC glGetProgramiv = nullptr;
    //    PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog = nullptr;
    //    PFNGLDELETEPROGRAMPROC glDeleteProgram = nullptr;
    //    PFNGLUSEPROGRAMPROC glUseProgram = nullptr;
    //    PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation = nullptr;
    //    PFNGLUNIFORM1IPROC glUniform1i = nullptr;
    //    PFNGLACTIVETEXTUREPROC glActiveTexture_ = nullptr;
    //    PFNGLUNIFORM4FVPROC
    //        glUniform4fv
    //            = nullptr;
    //            PFNGLUNIFORMMATRIX3FVPROC glUniformMatrix3fv = nullptr;

    //            PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer = nullptr;
    //            PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray = nullptr;
    //            PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray = nullptr;

    //    void EngineCore::Init (bool versionCritical, int width, int height, std::string windowName)
    //    {
    //        auto checkVersion = CheckVersion ();
    //        if (!checkVersion)
    //        {
    //            if (versionCritical)
    //            {
    //                std::cerr << "FAILURE in CheckVersion: version.compiled != version.linked" << std::endl;
    //                exit (EXIT_FAILURE);
    //            }
    //            else
    //                std::clog << "WARNING in CheckVersion: version.compiled != version.linked" << std::endl;
    //        }
    //        else
    //        {
    //            std::clog << "SUCCES in CheckVersion" << std::endl;
    //        }

    //        if (SDL_Init (SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    //        {
    //            std::cerr << "FAILURE in Init : Unable to init SDL, error: " << SDL_GetError () << std::endl;
    //            exit (EXIT_FAILURE);
    //        }
    //        else
    //        {
    //            std::clog << "SUCCES in Init : Init SDL" << std::endl;
    //        }

    //        window = SDL_CreateWindow (windowName.c_str (), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, ::SDL_WINDOW_OPENGL);

    //        if (window == nullptr)
    //        {
    //            std::cerr << "FAILURE in Init : Unable to create window, error: " << SDL_GetError () << std::endl;
    //            exit (EXIT_FAILURE);
    //        }
    //        else
    //        {
    //            std::clog << "SUCCES in Init : Create Window" << std::endl;
    //        }
    //        /*SDL_GLContext glcontext =*/SDL_GL_CreateContext (window);

    //        if (!InitGl ())
    //            exit (EXIT_FAILURE);
    //    }
    //    bool EngineCore::InitGl ()
    //    {
    //        try
    //        {
    //            load_gl_func ("glCreateShader", glCreateShader);
    //            load_gl_func ("glShaderSource", glShaderSource);
    //            load_gl_func ("glCompileShader", glCompileShader);
    //            load_gl_func ("glGetShaderiv", glGetShaderiv);
    //            load_gl_func ("glGetShaderInfoLog", glGetShaderInfoLog);
    //            load_gl_func ("glDeleteShader", glDeleteShader);
    //            load_gl_func ("glCreateProgram", glCreateProgram);
    //            load_gl_func ("glAttachShader", glAttachShader);
    //            load_gl_func ("glBindAttribLocation", glBindAttribLocation);
    //            load_gl_func ("glLinkProgram", glLinkProgram);
    //            load_gl_func ("glGetProgramiv", glGetProgramiv);
    //            load_gl_func ("glGetProgramInfoLog", glGetProgramInfoLog);
    //            load_gl_func ("glDeleteProgram", glDeleteProgram);
    //            load_gl_func ("glUseProgram", glUseProgram);
    //            load_gl_func ("glVertexAttribPointer", glVertexAttribPointer);
    //            load_gl_func ("glEnableVertexAttribArray", glEnableVertexAttribArray);
    //            load_gl_func ("glDisableVertexAttribArray", glDisableVertexAttribArray);
    //            load_gl_func ("glGetUniformLocation", glGetUniformLocation);
    //            load_gl_func ("glUniform1i", glUniform1i);
    //            load_gl_func ("glActiveTexture", glActiveTexture_);
    //            load_gl_func ("glUniform4fv", glUniform4fv);
    //            load_gl_func ("glUniformMatrix3fv", glUniformMatrix3fv);
    //        }
    //        catch (std::exception& ex)
    //        {
    //            std::cerr << ex.what ();
    //            return false;
    //        }

    //        shader00 = new shader_gl_es20 (R"(
    //                                       attribute vec2 a_position;
    //                                       void main()
    //                                       {
    //                                       gl_Position = vec4(a_position, 0.0, 1.0);
    //                                       }
    //                                       )",
    //                                       R"(
    //                                       uniform vec4 u_color;
    //                                       void main()
    //                                       {
    //                                       gl_FragColor = u_color;
    //                                       }
    //                                       )",
    //                                       {{0, "a_position"}});

    //        shader00->use ();
    //        shader00->set_uniform ("u_color", Color (1.f, 0.f, 0.f, 1.f));

    //        shader01 = new shader_gl_es20 (
    //            R"(
    //                    attribute vec2 a_position;
    //                    attribute vec4 a_color;
    //                    varying vec4 v_color;
    //                    void main()
    //                    {
    //                    v_color = a_color;
    //                    gl_Position = vec4(a_position, 0.0, 1.0);
    //                    }
    //                    )",
    //            R"(
    //                    varying vec4 v_color;
    //                    void main()
    //                    {
    //                    gl_FragColor = v_color;
    //                    }
    //                    )",
    //            {{0, "a_position"}, {1, "a_color"}});

    //        shader01->use ();

    //        shader02 = new shader_gl_es20 (
    //            R"(
    //                    attribute vec2 a_position;
    //                    attribute vec2 a_tex_coord;
    //                    attribute vec4 a_color;
    //                    varying vec4 v_color;
    //                    varying vec2 v_tex_coord;
    //                    void main()
    //                    {
    //                    v_tex_coord = a_tex_coord;
    //                    v_color = a_color;
    //                    gl_Position = vec4(a_position, 0.0, 1.0);
    //                    }
    //                    )",
    //            R"(
    //                    varying vec2 v_tex_coord;
    //                    varying vec4 v_color;
    //                    uniform sampler2D s_texture;
    //                    void main()
    //                    {
    //                    gl_FragColor = texture2D(s_texture, v_tex_coord) * v_color;
    //                    }
    //                    )",
    //            {{0, "a_position"}, {1, "a_color"}, {2, "a_tex_coord"}});

    //        // turn on rendering with just created shader program
    //        shader02->use ();

    //        shader03 = new shader_gl_es20 (
    //            R"(
    //                    uniform mat3 u_matrix;
    //                    attribute vec2 a_position;
    //                    attribute vec2 a_tex_coord;
    //                    attribute vec4 a_color;
    //                    varying vec4 v_color;
    //                    varying vec2 v_tex_coord;
    //                    void main()
    //                    {
    //                    v_tex_coord = a_tex_coord;
    //                    v_color = a_color;
    //                    vec3 pos = vec3(a_position, 1.0) * u_matrix;
    //                    gl_Position = vec4(pos, 1.0);
    //                    }
    //                    )",
    //            R"(
    //                    varying vec2 v_tex_coord;
    //                    varying vec4 v_color;
    //                    uniform sampler2D s_texture;
    //                    void main()
    //                    {
    //                    gl_FragColor = texture2D(s_texture, v_tex_coord) * v_color;
    //                    }
    //                    )",
    //            {{0, "a_position"}, {1, "a_color"}, {2, "a_tex_coord"}});
    //        shader03->use ();

    //        glEnable (GL_BLEND);
    //        GL_ERROR_CHECK ();
    //        glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //        GL_ERROR_CHECK ();

    //        glClearColor (0.f, 0.0, 0.f, 0.0f);
    //        GL_ERROR_CHECK ();

    //        glViewport (0, 0, 640, 480);
    //        GL_ERROR_CHECK ();
    //        return true;
    //    }
}
