#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_opengl_glext.h>
#include <cstdio>
#include <iostream>
#include <string_view>
#include <vector>

#include "engine.h"

static PFNGLCREATESHADERPROC glCreateShader = nullptr;
static PFNGLSHADERSOURCEARBPROC glShaderSource = nullptr;
static PFNGLCOMPILESHADERARBPROC glCompileShader = nullptr;
static PFNGLGETSHADERIVPROC glGetShaderiv = nullptr;
static PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog = nullptr;
static PFNGLDELETESHADERPROC glDeleteShader = nullptr;
static PFNGLCREATEPROGRAMPROC glCreateProgram = nullptr;
static PFNGLATTACHSHADERPROC glAttachShader = nullptr;
static PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation = nullptr;
static PFNGLLINKPROGRAMPROC glLinkProgram = nullptr;
static PFNGLGETPROGRAMIVPROC glGetProgramiv = nullptr;
static PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog = nullptr;
static PFNGLDELETEPROGRAMPROC glDeleteProgram = nullptr;
static PFNGLUSEPROGRAMPROC glUseProgram = nullptr;
static PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer = nullptr;
static PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray = nullptr;

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

std::istream& operator>> (std::istream& is, LumenAusf::vertex& v)
{
    is >> v.x;
    is >> v.y;
    return is;
}

std::istream& operator>> (std::istream& is, LumenAusf::triangle& t)
{
    is >> t.v[0];
    is >> t.v[1];
    is >> t.v[2];
    return is;
}

namespace LumenAusf
{
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
        bool DrawTriangle (const triangle& t);

        SDL_Window* window;
        static EngineCore* EnCore;
    };

    EngineCore* EngineCore::EnCore = nullptr;

    Engine::Engine ()
    {
        if (LumenAusf::EngineCore::EnCore == nullptr)
            EngineCore::EnCore = new EngineCore ();
    }

    void Engine::Init (bool versionCritical, int width, int height, std::string windowName)
    {
        EngineCore::EnCore->Init (versionCritical, width, height, windowName);
    }

    void Engine::ReadEvent () { EngineCore::EnCore->ReadEvent (this); }

    void Engine::Finish () { EngineCore::EnCore->Finish (); }

    bool Engine::DrawTriangle (const triangle& t) { return EngineCore::EnCore->DrawTriangle (t); }

    EngineCore::EngineCore () { std::clog << "Create Engine" << std::endl; }

    EngineCore::~EngineCore ()
    {
        EnCore = nullptr;
        std::clog << "Destroy Engine" << std::endl;
    }

    void EngineCore::Init (bool versionCritical, int width, int height, std::string windowName)
    {
        auto checkVersion = CheckVersion ();
        if (!checkVersion)
        {
            if (versionCritical)
            {
                std::cerr << "FAILURE in CheckVersion: version.compiled != version.linked" << std::endl;
                exit (EXIT_FAILURE);
            }
            else
                std::clog << "WARNING in CheckVersion: version.compiled != version.linked" << std::endl;
        }
        else
        {
            std::clog << "SUCCES in CheckVersion" << std::endl;
        }

        if (SDL_Init (SDL_INIT_VIDEO) < 0)
        {
            std::cerr << "FAILURE in Init : Unable to init SDL, error: " << SDL_GetError () << std::endl;
            exit (EXIT_FAILURE);
        }
        else
        {
            std::clog << "SUCCES in Init : Init SDL" << std::endl;
        }

        window = SDL_CreateWindow (windowName.c_str (), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, ::SDL_WINDOW_OPENGL);

        if (window == nullptr)
        {
            std::cerr << "FAILURE in Init : Unable to create window, error: " << SDL_GetError () << std::endl;
            exit (EXIT_FAILURE);
        }
        else
        {
            std::clog << "SUCCES in Init : Create Window" << std::endl;
        }
        /*SDL_GLContext glcontext =*/SDL_GL_CreateContext (window);

        if (!InitGl ())
            exit (EXIT_FAILURE);
    }

    bool EngineCore::InitGl ()
    {
        try
        {
            load_gl_func ("glCreateShader", glCreateShader);
            load_gl_func ("glShaderSource", glShaderSource);
            load_gl_func ("glCompileShader", glCompileShader);
            load_gl_func ("glGetShaderiv", glGetShaderiv);
            load_gl_func ("glGetShaderInfoLog", glGetShaderInfoLog);
            load_gl_func ("glDeleteShader", glDeleteShader);
            load_gl_func ("glCreateProgram", glCreateProgram);
            load_gl_func ("glAttachShader", glAttachShader);
            load_gl_func ("glBindAttribLocation", glBindAttribLocation);
            load_gl_func ("glLinkProgram", glLinkProgram);
            load_gl_func ("glGetProgramiv", glGetProgramiv);
            load_gl_func ("glGetProgramInfoLog", glGetProgramInfoLog);
            load_gl_func ("glDeleteProgram", glDeleteProgram);
            load_gl_func ("glUseProgram", glUseProgram);
            load_gl_func ("glVertexAttribPointer", glVertexAttribPointer);
            load_gl_func ("glEnableVertexAttribArray", glEnableVertexAttribArray);
        }
        catch (std::exception& ex)
        {
            std::cerr << ex.what ();
            return false;
        }

        GLuint vert_shader = glCreateShader (GL_VERTEX_SHADER);
        std::string_view vertex_shader_src = R"(
       attribute vec2 a_position;
       void main()
       {
           gl_Position = vec4(a_position, 0.0, 1.0);
       }
       )";
        const char* source = vertex_shader_src.data ();
        glShaderSource (vert_shader, 1, &source, nullptr);

        glCompileShader (vert_shader);

        GLint compiled_status = 0;
        glGetShaderiv (vert_shader, GL_COMPILE_STATUS, &compiled_status);
        if (compiled_status == 0)
        {
            GLint info_len = 0;
            glGetShaderiv (vert_shader, GL_INFO_LOG_LENGTH, &info_len);
            std::vector<char> info_chars (info_len);
            glGetShaderInfoLog (vert_shader, info_len, NULL, info_chars.data ());
            glDeleteShader (vert_shader);

            std::string shader_type_name = "vertex";
            std::cerr << "Error compiling shader(vertex)\n" << vertex_shader_src << "\n" << info_chars.data ();
            return false;
        }

        // create fragment shader

        GLuint fragment_shader = glCreateShader (GL_FRAGMENT_SHADER);
        std::string_view fragment_shader_src = R"(
       void main()
       {
           gl_FragColor = vec4(1.0, 0.5, 1.0, 1.0);
       }
       )";
        source = fragment_shader_src.data ();
        glShaderSource (fragment_shader, 1, &source, nullptr);

        glCompileShader (fragment_shader);

        compiled_status = 0;
        glGetShaderiv (fragment_shader, GL_COMPILE_STATUS, &compiled_status);
        if (compiled_status == 0)
        {
            GLint info_len = 0;
            glGetShaderiv (fragment_shader, GL_INFO_LOG_LENGTH, &info_len);
            std::vector<char> info_chars (info_len);
            glGetShaderInfoLog (fragment_shader, info_len, NULL, info_chars.data ());
            glDeleteShader (fragment_shader);

            std::cerr << "Error compiling shader(fragment)\n" << vertex_shader_src << "\n" << info_chars.data ();
            return false;
        }

        // now create program and attach vertex and fragment shaders

        GLuint program_id_ = glCreateProgram ();
        if (0 == program_id_)
        {
            std::cerr << "failed to create gl program";
            return false;
        }

        glAttachShader (program_id_, vert_shader);
        glAttachShader (program_id_, fragment_shader);

        // bind attribute location
        glBindAttribLocation (program_id_, 0, "a_position");
        // link program after binding attribute locations
        glLinkProgram (program_id_);
        // Check the link status
        GLint linked_status = 0;
        glGetProgramiv (program_id_, GL_LINK_STATUS, &linked_status);
        if (linked_status == 0)
        {
            GLint infoLen = 0;
            glGetProgramiv (program_id_, GL_INFO_LOG_LENGTH, &infoLen);
            std::vector<char> infoLog (infoLen);
            glGetProgramInfoLog (program_id_, infoLen, NULL, infoLog.data ());
            std::cerr << "Error linking program:\n" << infoLog.data ();
            glDeleteProgram (program_id_);
            return false;
        }

        // turn on rendering with just created shader program
        glUseProgram (program_id_);
        return true;
    }

    bool EngineCore::CheckVersion ()
    {
        SDL_version compiled = {0, 0, 0};
        SDL_version linked = {0, 0, 0};

        SDL_VERSION (&compiled);
        SDL_GetVersion (&linked);

        auto result = compiled.major == linked.major && compiled.minor == linked.minor && compiled.patch == linked.patch;

        return result;
    }

    void EngineCore::ReadEvent (Engine* engine)
    {
        EventItem* event = new EventItem ();
        SDL_Event eventSDL;    // события SDL

        while (SDL_PollEvent (&eventSDL))
        {
            switch (eventSDL.type)
            {
                case SDL_QUIT:
                    event->typeEvent = TYPE_EVENT::QUIT;
                    engine->EngineEvent (event);
                    break;

                case SDL_KEYDOWN:
                    event->typeEvent = TYPE_EVENT::KEYDOWN;
                    switch (eventSDL.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                            event->keyCode = KEY_CODE::ESCAPE;
                            engine->EngineEvent (event);
                            break;
                        case SDLK_RETURN:
                            engine->EngineEvent (new EventItem);
                            break;
                        case SDLK_UP:
                            event->keyCode = KEY_CODE::UP;
                            engine->EngineEvent (event);
                            break;
                        case SDLK_LEFT:
                            event->keyCode = KEY_CODE::LEFT;
                            engine->EngineEvent (event);
                            break;
                        case SDLK_DOWN:
                            event->keyCode = KEY_CODE::DOWN;
                            engine->EngineEvent (event);
                            break;
                        case SDLK_RIGHT:
                            event->keyCode = KEY_CODE::RIGHT;
                            engine->EngineEvent (event);
                            break;
                        case SDLK_SPACE:
                            event->keyCode = KEY_CODE::SPACE;
                            engine->EngineEvent (event);
                    }
                    break;
            }
        }
    }

    void EngineCore::Finish () { this->~EngineCore (); }

    bool EngineCore::DrawTriangle (const triangle& t)
    {
        try
        {
            glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glVertexAttribPointer (0, 2, GL_FLOAT, GL_FALSE, sizeof (vertex), &t.v[0]);
            glEnableVertexAttribArray (0);
            glDrawArrays (GL_TRIANGLES, 0, 3);

            glFlush ();
            SDL_GL_SwapWindow (window);
        }
        catch (std::exception ex)
        {
            std::cerr << ex.what ();
            return false;
        }
        return true;
    }
}
