#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_opengl_glext.h>
#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string_view>
#include <tuple>
#include <vector>

#include "engine.h"
#include "picopng.hxx"

// we have to load all extension GL function pointers
// dynamically from OpenGL library
// so first declare function pointers for all we need
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
static PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray = nullptr;
static PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation = nullptr;
static PFNGLUNIFORM1IPROC glUniform1i = nullptr;
static PFNGLACTIVETEXTUREPROC glActiveTexture_ = nullptr;
static PFNGLUNIFORM4FVPROC glUniform4fv = nullptr;
static PFNGLUNIFORMMATRIX3FVPROC glUniformMatrix3fv = nullptr;

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
    tri0::tri0 () : v{v0 (), v0 (), v0 ()} {}

    tri1::tri1 () : v{v1 (), v1 (), v1 ()} {}

    tri2::tri2 () : v{v2 (), v2 (), v2 ()} {}

    vec2::vec2 () : x (0.f), y (0.f) {}
    vec2::vec2 (float x_, float y_) : x (x_), y (y_) {}

    vec2 operator+ (const vec2& l, const vec2& r)
    {
        vec2 result;
        result.x = l.x + r.x;
        result.y = l.y + r.y;
        return result;
    }

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

    vec2 operator* (const vec2& v, const mat2x3& m)
    {
        vec2 result;
        result.x = v.x * m.col0.x + v.y * m.col0.y + m.delta.x;
        result.y = v.x * m.col1.x + v.y * m.col1.y + m.delta.y;
        return result;
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

    color::color (std::uint32_t rgba_) : rgba (rgba_) {}

    color::color (float r, float g, float b, float a)
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

    texture::~texture () {}

    class texture_gl_es20 final : public texture
    {
       public:
        explicit texture_gl_es20 (std::string_view path);
        ~texture_gl_es20 () override;

        void bind () const
        {
            glBindTexture (GL_TEXTURE_2D, tex_handl);
            GL_ERROR_CHECK ();
        }

        std::uint32_t get_width () const final { return width; }
        std::uint32_t get_height () const final { return height; }

       private:
        std::string file_path;
        GLuint tex_handl = 0;
        std::uint32_t width = 0;
        std::uint32_t height = 0;
    };

    class shader_gl_es20
    {
       public:
        shader_gl_es20 (std::string_view vertex_src, std::string_view fragment_src, const std::vector<std::tuple<GLuint, const GLchar*>>& attributes)
        {
            vert_shader = compile_shader (GL_VERTEX_SHADER, vertex_src);
            frag_shader = compile_shader (GL_FRAGMENT_SHADER, fragment_src);
            if (vert_shader == 0 || frag_shader == 0)
            {
                throw std::runtime_error ("can't compile shader");
            }
            program_id = link_shader_program (attributes);
            if (program_id == 0)
            {
                throw std::runtime_error ("can't link shader");
            }
        }

        void use () const
        {
            glUseProgram (program_id);
            GL_ERROR_CHECK ();
        }

        void set_uniform (std::string_view uniform_name, texture_gl_es20* texture)
        {
            assert (texture != nullptr);
            const int location = glGetUniformLocation (program_id, uniform_name.data ());
            GL_ERROR_CHECK ();
            if (location == -1)
            {
                std::cerr << "can't get uniform location from shader\n";
                throw std::runtime_error ("can't get uniform location");
            }
            unsigned int texture_unit = 0;
            glActiveTexture_ (GL_TEXTURE0 + texture_unit);
            GL_ERROR_CHECK ();

            texture->bind ();

            // http://www.khronos.org/opengles/sdk/docs/man/xhtml/glUniform.xml
            glUniform1i (location, static_cast<int> (0 + texture_unit));
            GL_ERROR_CHECK ();
        }

        void set_uniform (std::string_view uniform_name, const color& c)
        {
            const int location = glGetUniformLocation (program_id, uniform_name.data ());
            GL_ERROR_CHECK ();
            if (location == -1)
            {
                std::cerr << "can't get uniform location from shader\n";
                throw std::runtime_error ("can't get uniform location");
            }
            float values[4] = {c.get_r (), c.get_g (), c.get_b (), c.get_a ()};
            glUniform4fv (location, 1, &values[0])
                ;
                GL_ERROR_CHECK ();
        }

        void set_uniform (std::string_view uniform_name, const mat2x3& m)
        {
            const int location = glGetUniformLocation (program_id, uniform_name.data ());
            GL_ERROR_CHECK ();
            if (location == -1)
            {
                std::cerr << "can't get uniform location from shader\n";
                throw std::runtime_error ("can't get uniform location");
            }
            // OpenGL wants matrix in column major order
            // clang-format off
            float values[9] = { m.col0.x,  m.col0.y, m.delta.x,
                                m.col1.x, m.col1.y, m.delta.y,
                                0.f,      0.f,       1.f };
            // clang-format on
            glUniformMatrix3fv (location, 1, GL_FALSE, &values[0]);
            GL_ERROR_CHECK ();
        }

       private:
        GLuint compile_shader (GLenum shader_type, std::string_view src)
        {
            GLuint shader_id = glCreateShader (shader_type);
            GL_ERROR_CHECK ();
            std::string_view vertex_shader_src = src;
            const char* source = vertex_shader_src.data ();
            glShaderSource (shader_id, 1, &source, nullptr);
            GL_ERROR_CHECK ();

            glCompileShader (shader_id);
            GL_ERROR_CHECK ();

            GLint compiled_status = 0;
            glGetShaderiv (shader_id, GL_COMPILE_STATUS, &compiled_status);
            GL_ERROR_CHECK ();
            if (compiled_status == 0)
            {
                GLint info_len = 0;
                glGetShaderiv (shader_id, GL_INFO_LOG_LENGTH, &info_len);
                GL_ERROR_CHECK ();
                std::vector<char> info_chars (static_cast<size_t> (info_len));
                glGetShaderInfoLog (shader_id, info_len, NULL, info_chars.data ());
                GL_ERROR_CHECK ();
                glDeleteShader (shader_id);
                GL_ERROR_CHECK ();

                std::string shader_type_name = shader_type == GL_VERTEX_SHADER ? "vertex" : "fragment";
                std::cerr << "Error compiling shader(vertex)\n" << vertex_shader_src << "\n" << info_chars.data ();
                return 0;
            }
            return shader_id;
        }
        GLuint link_shader_program (const std::vector<std::tuple<GLuint, const GLchar*>>& attributes)
        {
            GLuint program_id_ = glCreateProgram ();
            GL_ERROR_CHECK ();
            if (0 == program_id_)
            {
                std::cerr << "failed to create gl program";
                throw std::runtime_error ("can't link shader");
            }

            glAttachShader (program_id_, vert_shader);
            GL_ERROR_CHECK ();
            glAttachShader (program_id_, frag_shader);
            GL_ERROR_CHECK ();

            // bind attribute location
            for (const auto& attr : attributes)
            {
                GLuint loc = std::get<0> (attr);
                const GLchar* name = std::get<1> (attr);
                glBindAttribLocation (program_id_, loc, name);
                GL_ERROR_CHECK ();
            }

            // link program after binding attribute locations
            glLinkProgram (program_id_);
            GL_ERROR_CHECK ();
            // Check the link status
            GLint linked_status = 0;
            glGetProgramiv (program_id_, GL_LINK_STATUS, &linked_status);
            GL_ERROR_CHECK ();
            if (linked_status == 0)
            {
                GLint infoLen = 0;
                glGetProgramiv (program_id_, GL_INFO_LOG_LENGTH, &infoLen);
                GL_ERROR_CHECK ();
                std::vector<char> infoLog (static_cast<size_t> (infoLen));
                glGetProgramInfoLog (program_id_, infoLen, NULL, infoLog.data ());
                GL_ERROR_CHECK ();
                std::cerr << "Error linking program:\n" << infoLog.data ();
                glDeleteProgram (program_id_);
                GL_ERROR_CHECK ();
                return 0;
            }
            return program_id_;
        }

        GLuint vert_shader = 0;
        GLuint frag_shader = 0;
        GLuint program_id = 0;
    };

    std::istream& operator>> (std::istream& is, mat2x3& m)
    {
        is >> m.col0.x;
        is >> m.col1.x;
        is >> m.col0.y;
        is >> m.col1.y;
        return is;
    }

    std::istream& operator>> (std::istream& is, vec2& v)
    {
        is >> v.x;
        is >> v.y;
        return is;
    }

    std::istream& operator>> (std::istream& is, color& c)
    {
        float r = 0.f;
        float g = 0.f;
        float b = 0.f;
        float a = 0.f;
        is >> r;
        is >> g;
        is >> b;
        is >> a;
        c = color (r, g, b, a);
        return is;
    }

    std::istream& operator>> (std::istream& is, v0& v)
    {
        is >> v.pos.x;
        is >> v.pos.y;

        return is;
    }

    std::istream& operator>> (std::istream& is, v1& v)
    {
        is >> v.pos.x;
        is >> v.pos.y;
        is >> v.c;
        return is;
    }

    std::istream& operator>> (std::istream& is, v2& v)
    {
        is >> v.pos.x;
        is >> v.pos.y;
        is >> v.uv;
        is >> v.c;
        return is;
    }

    std::istream& operator>> (std::istream& is, tri0& t)
    {
        is >> t.v[0];
        is >> t.v[1];
        is >> t.v[2];
        return is;
    }

    std::istream& operator>> (std::istream& is, tri1& t)
    {
        is >> t.v[0];
        is >> t.v[1];
        is >> t.v[2];
        return is;
    }

    std::istream& operator>> (std::istream& is, tri2& t)
    {
        is >> t.v[0];
        is >> t.v[1];
        is >> t.v[2];
        return is;
    }

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
        texture* CreateTexture (std::string_view path);
        void DestroyTexture (texture* t);
        //        bool DrawTriangle (const triangle& t);
        void DrawTriangle (const tri0& t, const color& c);
        void DrawTriangle (const tri1& t);
        void DrawTriangle (const tri2& t, texture* tex);
        void DrawTriangle (const tri2& t, texture* tex, const mat2x3& m);
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

    texture* Engine::CreateTexture (std::string_view path) { return EngineCore::EnCore->CreateTexture (path); }

    void Engine::DestroyTexture (texture* t) { EngineCore::EnCore->DestroyTexture (t); }

    void Engine::DrawTriangle (const tri0& t, const color& c) { EngineCore::EnCore->DrawTriangle (t, c); }

    void Engine::DrawTriangle (const tri1& t) { EngineCore::EnCore->DrawTriangle (t); }

    void Engine::DrawTriangle (const tri2& t, texture* tex) { EngineCore::EnCore->DrawTriangle (t, tex); }

    void Engine::DrawTriangle (const tri2& t, texture* tex, const mat2x3& m) { EngineCore::EnCore->DrawTriangle (t, tex, m); }

    float Engine::getTimeFromInit () { return EngineCore::EnCore->getTimeFromInit (); }

    void Engine::SwapBuffers () { EngineCore::EnCore->SwapBuffers (); }

    //    bool Engine::DrawTriangle (const triangle& t) { return EngineCore::EnCore->DrawTriangle (t); }

    void Engine::Clear () { EngineCore::EnCore->Clear (); }

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
            load_gl_func ("glDisableVertexAttribArray", glDisableVertexAttribArray);
            load_gl_func ("glGetUniformLocation", glGetUniformLocation);
            load_gl_func ("glUniform1i", glUniform1i);
            load_gl_func ("glActiveTexture", glActiveTexture_);
            load_gl_func ("glUniform4fv", glUniform4fv);
            load_gl_func ("glUniformMatrix3fv", glUniformMatrix3fv);
        }
        catch (std::exception& ex)
        {
            return ex.what ();
        }

        shader00 = new shader_gl_es20 (R"(
                                      attribute vec2 a_position;
                                      void main()
                                      {
                                      gl_Position = vec4(a_position, 0.0, 1.0);
                                      }
                                      )",
                                       R"(
                                      uniform vec4 u_color;
                                      void main()
                                      {
                                      gl_FragColor = u_color;
                                      }
                                      )",
                                       {{0, "a_position"}});

        shader00->use ();
        shader00->set_uniform ("u_color", color (1.f, 0.f, 0.f, 1.f));

        shader01 = new shader_gl_es20 (
            R"(
                    attribute vec2 a_position;
                    attribute vec4 a_color;
                    varying vec4 v_color;
                    void main()
                    {
                    v_color = a_color;
                    gl_Position = vec4(a_position, 0.0, 1.0);
                    }
                    )",
            R"(
                    varying vec4 v_color;
                    void main()
                    {
                    gl_FragColor = v_color;
                    }
                    )",
            {{0, "a_position"}, {1, "a_color"}});

        shader01->use ();

        shader02 = new shader_gl_es20 (
            R"(
                    attribute vec2 a_position;
                    attribute vec2 a_tex_coord;
                    attribute vec4 a_color;
                    varying vec4 v_color;
                    varying vec2 v_tex_coord;
                    void main()
                    {
                    v_tex_coord = a_tex_coord;
                    v_color = a_color;
                    gl_Position = vec4(a_position, 0.0, 1.0);
                    }
                    )",
            R"(
                    varying vec2 v_tex_coord;
                    varying vec4 v_color;
                    uniform sampler2D s_texture;
                    void main()
                    {
                    gl_FragColor = texture2D(s_texture, v_tex_coord) * v_color;
                    }
                    )",
            {{0, "a_position"}, {1, "a_color"}, {2, "a_tex_coord"}});

        // turn on rendering with just created shader program
        shader02->use ();

        shader03 = new shader_gl_es20 (
            R"(
                    uniform mat3 u_matrix;
                    attribute vec2 a_position;
                    attribute vec2 a_tex_coord;
                    attribute vec4 a_color;
                    varying vec4 v_color;
                    varying vec2 v_tex_coord;
                    void main()
                    {
                    v_tex_coord = a_tex_coord;
                    v_color = a_color;
                    vec3 pos = vec3(a_position, 1.0) * u_matrix;
                    gl_Position = vec4(pos, 1.0);
                    }
                    )",
            R"(
                    varying vec2 v_tex_coord;
                    varying vec4 v_color;
                    uniform sampler2D s_texture;
                    void main()
                    {
                    gl_FragColor = texture2D(s_texture, v_tex_coord) * v_color;
                    }
                    )",
            {{0, "a_position"}, {1, "a_color"}, {2, "a_tex_coord"}});
        shader03->use ();

        glEnable (GL_BLEND);
        GL_ERROR_CHECK ();
        glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        GL_ERROR_CHECK ();

        glClearColor (0.f, 0.0, 0.f, 0.0f);
        GL_ERROR_CHECK ();

        glViewport (0, 0, 640, 480);
        GL_ERROR_CHECK ();
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

    texture* EngineCore::CreateTexture (std::string_view path) { return new texture_gl_es20 (path); }

    void EngineCore::DestroyTexture (texture* t) { delete t; }

    void EngineCore::DrawTriangle (const tri0& t, const color& c)
    {
        shader00->use ();
        shader00->set_uniform ("u_color", c);
        // vertex coordinates
        glVertexAttribPointer (0, 2, GL_FLOAT, GL_FALSE, sizeof (v0), &t.v[0].pos.x);
        GL_ERROR_CHECK ();
        glEnableVertexAttribArray (0);
        GL_ERROR_CHECK ();

        glDrawArrays (GL_TRIANGLES, 0, 3);
        GL_ERROR_CHECK ();
    }

    void EngineCore::DrawTriangle (const tri1& t)
    {
        shader01->use ();
        // positions
        glVertexAttribPointer (0, 2, GL_FLOAT, GL_FALSE, sizeof (t.v[0]), &t.v[0].pos);
        GL_ERROR_CHECK ();
        glEnableVertexAttribArray (0);
        GL_ERROR_CHECK ();
        // colors
        glVertexAttribPointer (1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof (t.v[0]), &t.v[0].c);
        GL_ERROR_CHECK ();
        glEnableVertexAttribArray (1);
        GL_ERROR_CHECK ();

        glDrawArrays (GL_TRIANGLES, 0, 3);
        GL_ERROR_CHECK ();

        glDisableVertexAttribArray (1);
        GL_ERROR_CHECK ();
    }

    void EngineCore::DrawTriangle (const tri2& t, texture* tex)
    {
        shader02->use ();
        texture_gl_es20* texture = static_cast<texture_gl_es20*> (tex);
        texture->bind ();
        shader02->set_uniform ("s_texture", texture);
        // positions
        glVertexAttribPointer (0, 2, GL_FLOAT, GL_FALSE, sizeof (t.v[0]), &t.v[0].pos);
        GL_ERROR_CHECK ();
        glEnableVertexAttribArray (0);
        GL_ERROR_CHECK ();
        // colors
        glVertexAttribPointer (1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof (t.v[0]), &t.v[0].c);
        GL_ERROR_CHECK ();
        glEnableVertexAttribArray (1);
        GL_ERROR_CHECK ();

        // texture coordinates
        glVertexAttribPointer (2, 2, GL_FLOAT, GL_FALSE, sizeof (t.v[0]), &t.v[0].uv);
        GL_ERROR_CHECK ();
        glEnableVertexAttribArray (2);
        GL_ERROR_CHECK ();

        glDrawArrays (GL_TRIANGLES, 0, 3);
        GL_ERROR_CHECK ();

        glDisableVertexAttribArray (1);
        GL_ERROR_CHECK ();
        glDisableVertexAttribArray (2);
        GL_ERROR_CHECK ();
    }

    void EngineCore::DrawTriangle (const tri2& t, texture* tex, const mat2x3& m)
    {
        shader03->use ();
        texture_gl_es20* texture = static_cast<texture_gl_es20*> (tex);
        texture->bind ();
        shader03->set_uniform ("s_texture", texture);
        shader03->set_uniform ("u_matrix", m);
        // positions
        glVertexAttribPointer (0, 2, GL_FLOAT, GL_FALSE, sizeof (t.v[0]), &t.v[0].pos);
        GL_ERROR_CHECK ();
        glEnableVertexAttribArray (0);
        GL_ERROR_CHECK ();
        // colors
        glVertexAttribPointer (1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof (t.v[0]), &t.v[0].c);
        GL_ERROR_CHECK ();
        glEnableVertexAttribArray (1);
        GL_ERROR_CHECK ();

        // texture coordinates
        glVertexAttribPointer (2, 2, GL_FLOAT, GL_FALSE, sizeof (t.v[0]), &t.v[0].uv);
        GL_ERROR_CHECK ();
        glEnableVertexAttribArray (2);
        GL_ERROR_CHECK ();

        glDrawArrays (GL_TRIANGLES, 0, 3);
        GL_ERROR_CHECK ();

        glDisableVertexAttribArray (1);
        GL_ERROR_CHECK ();
        glDisableVertexAttribArray (2);
        GL_ERROR_CHECK ();
    }

    void EngineCore::Clear () { glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

    bool EngineCore::LoadTexture (std::string path)
    {
        std::vector<unsigned char> png_file_in_memory;
        std::ifstream ifs (path.data (), std::ios_base::binary);
        if (!ifs)
        {
            return false;
        }
        ifs.seekg (0, std::ios_base::end);
        size_t pos_in_file = ifs.tellg ();
        png_file_in_memory.resize (pos_in_file);
        ifs.seekg (0, std::ios_base::beg);
        if (!ifs)
        {
            return false;
        }

        ifs.read (reinterpret_cast<char*> (png_file_in_memory.data ()), pos_in_file);
        if (!ifs.good ())
        {
            return false;
        }

        std::vector<unsigned char> image;
        unsigned long w = 0;
        unsigned long h = 0;
        int error = decodePNG (image, w, h, &png_file_in_memory[0], png_file_in_memory.size (), false);

        // if there's an error, display it
        if (error != 0)
        {
            std::cerr << "error: " << error << std::endl;
            return false;
        }

        GLuint tex_handl = 0;
        glGenTextures (1, &tex_handl);
        //            OM_GL_CHECK();
        glBindTexture (GL_TEXTURE_2D, tex_handl);
        //            OM_GL_CHECK();

        GLint mipmap_level = 0;
        GLint border = 0;
        glTexImage2D (GL_TEXTURE_2D, mipmap_level, GL_RGBA, w, h, border, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);
        //            OM_GL_CHECK();

        glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        //            OM_GL_CHECK();
        glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        //            OM_GL_CHECK();
        return true;
    }

    void EngineCore::SwapBuffers ()
    {
        glClearColor (0.5, 0.5, 0, 1);
        SDL_GL_SwapWindow (window);
        glClear (GL_COLOR_BUFFER_BIT);
        GL_ERROR_CHECK ();
    }

    float EngineCore::getTimeFromInit ()
    {
        std::uint32_t ms_from_library_initialization = SDL_GetTicks ();
        float seconds = ms_from_library_initialization * 0.001f;
        return seconds;
    }

    texture_gl_es20::texture_gl_es20 (std::string_view path) : file_path (path)
    {
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
        int error = decodePNG (image, w, h, &png_file_in_memory[0], png_file_in_memory.size (), false);

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

    float color::get_r () const
    {
        std::uint32_t r_ = (rgba & 0x000000FF) >> 0;
        return r_ / 255.f;
    }
    float color::get_g () const
    {
        std::uint32_t g_ = (rgba & 0x0000FF00) >> 8;
        return g_ / 255.f;
    }
    float color::get_b () const
    {
        std::uint32_t b_ = (rgba & 0x00FF0000) >> 16;
        return b_ / 255.f;
    }
    float color::get_a () const
    {
        std::uint32_t a_ = (rgba & 0xFF000000) >> 24;
        return a_ / 255.f;
    }

    void color::set_r (const float r)
    {
        std::uint32_t r_ = static_cast<std::uint32_t> (r * 255);
        rgba &= 0xFFFFFF00;
        rgba |= (r_ << 0);
    }
    void color::set_g (const float g)
    {
        std::uint32_t g_ = static_cast<std::uint32_t> (g * 255);
        rgba &= 0xFFFF00FF;
        rgba |= (g_ << 8);
    }
    void color::set_b (const float b)
    {
        std::uint32_t b_ = static_cast<std::uint32_t> (b * 255);
        rgba &= 0xFF00FFFF;
        rgba |= (b_ << 16);
    }
    void color::set_a (const float a)
    {
        std::uint32_t a_ = static_cast<std::uint32_t> (a * 255);
        rgba &= 0x00FFFFFF;
        rgba |= a_ << 24;
    }
}
