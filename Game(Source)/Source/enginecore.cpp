#include "enginecore.h"

namespace LumenAusf
{
    EngineCore::EngineCore () { std::clog << "Create Engine" << std::endl; }

    Glfunc* Glfunc::ptr = nullptr;

    EngineCore::~EngineCore ()
    {
        EnCore = nullptr;
        std::clog << "Destroy Engine" << std::endl;
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

    Texture* EngineCore::CreateTexture (std::string_view path, int hCount, int wCount) { return new texture_gl_es20 (path, hCount, wCount); }

    void EngineCore::DestroyTexture (Texture* t) { t->~Texture (); }

    void EngineCore::DrawTriangle (const tri0& t, const Color& c)
    {
        shader00->use ();
        shader00->set_uniform ("u_color", c);
        // vertex coordinates
        Glfunc::Get ()->glVertexAttribPointer (0, 2, GL_FLOAT, GL_FALSE, sizeof (v0), &t.v[0].pos.x);
        GL_ERROR_CHECK ();
        Glfunc::Get ()->glEnableVertexAttribArray (0);
        GL_ERROR_CHECK ();

        glDrawArrays (GL_TRIANGLES, 0, 3);
        GL_ERROR_CHECK ();
    }

    void EngineCore::DrawTriangle (const tri1& t)
    {
        shader01->use ();
        // positions
        Glfunc::Get ()->glVertexAttribPointer (0, 2, GL_FLOAT, GL_FALSE, sizeof (t.v[0]), &t.v[0].pos);
        GL_ERROR_CHECK ();
        Glfunc::Get ()->glEnableVertexAttribArray (0);
        GL_ERROR_CHECK ();
        // colors
        Glfunc::Get ()->glVertexAttribPointer (1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof (t.v[0]), &t.v[0].c);
        GL_ERROR_CHECK ();
        Glfunc::Get ()->glEnableVertexAttribArray (1);
        GL_ERROR_CHECK ();

        glDrawArrays (GL_TRIANGLES, 0, 3);
        GL_ERROR_CHECK ();

        Glfunc::Get ()->glDisableVertexAttribArray (1);
        GL_ERROR_CHECK ();
    }

    void EngineCore::DrawTriangle (const tri2& t, Texture* tex)
    {
        shader02->use ();
        texture_gl_es20* texture = static_cast<texture_gl_es20*> (tex);
        texture->bind ();
        shader02->set_uniform ("s_texture", texture);
        // positions
        Glfunc::Get ()->glVertexAttribPointer (0, 2, GL_FLOAT, GL_FALSE, sizeof (t.v[0]), &t.v[0].pos);
        GL_ERROR_CHECK ();
        Glfunc::Get ()->glEnableVertexAttribArray (0);
        GL_ERROR_CHECK ();
        // colors
        Glfunc::Get ()->glVertexAttribPointer (1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof (t.v[0]), &t.v[0].c);
        GL_ERROR_CHECK ();
        Glfunc::Get ()->glEnableVertexAttribArray (1);
        GL_ERROR_CHECK ();

        // texture coordinates
        Glfunc::Get ()->glVertexAttribPointer (2, 2, GL_FLOAT, GL_FALSE, sizeof (t.v[0]), &t.v[0].uv);
        GL_ERROR_CHECK ();
        Glfunc::Get ()->glEnableVertexAttribArray (2);
        GL_ERROR_CHECK ();

        glDrawArrays (GL_TRIANGLES, 0, 3);
        GL_ERROR_CHECK ();

        Glfunc::Get ()->glDisableVertexAttribArray (1);
        GL_ERROR_CHECK ();
        Glfunc::Get ()->glDisableVertexAttribArray (2);
        GL_ERROR_CHECK ();
    }

    void EngineCore::DrawTriangle (const tri2& t, Texture* tex, const mat2x3& m)
    {
        shader03->use ();
        texture_gl_es20* texture = static_cast<texture_gl_es20*> (tex);
        texture->bind ();
        shader03->set_uniform ("s_texture", texture);
        shader03->set_uniform ("u_matrix", m);
        // positions
        Glfunc::Get ()->glVertexAttribPointer (0, 2, GL_FLOAT, GL_FALSE, sizeof (t.v[0]), &t.v[0].pos);
        GL_ERROR_CHECK ();
        Glfunc::Get ()->glEnableVertexAttribArray (0);
        GL_ERROR_CHECK ();
        // colors
        Glfunc::Get ()->glVertexAttribPointer (1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof (t.v[0]), &t.v[0].c);
        GL_ERROR_CHECK ();
        Glfunc::Get ()->glEnableVertexAttribArray (1);
        GL_ERROR_CHECK ();

        // texture coordinates
        Glfunc::Get ()->glVertexAttribPointer (2, 2, GL_FLOAT, GL_FALSE, sizeof (t.v[0]), &t.v[0].uv);
        GL_ERROR_CHECK ();
        Glfunc::Get ()->glEnableVertexAttribArray (2);
        GL_ERROR_CHECK ();

        glDrawArrays (GL_TRIANGLES, 0, 3);
        GL_ERROR_CHECK ();

        Glfunc::Get ()->glDisableVertexAttribArray (1);
        GL_ERROR_CHECK ();
        Glfunc::Get ()->glDisableVertexAttribArray (2);
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

        if (SDL_Init (SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
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
            load_gl_func ("glCreateShader", Glfunc::Get ()->glCreateShader);
            load_gl_func ("glShaderSource", Glfunc::Get ()->glShaderSource);
            load_gl_func ("glCompileShader", Glfunc::Get ()->glCompileShader);
            load_gl_func ("glGetShaderiv", Glfunc::Get ()->glGetShaderiv);
            load_gl_func ("glGetShaderInfoLog", Glfunc::Get ()->glGetShaderInfoLog);
            load_gl_func ("glDeleteShader", Glfunc::Get ()->glDeleteShader);
            load_gl_func ("glCreateProgram", Glfunc::Get ()->glCreateProgram);
            load_gl_func ("glAttachShader", Glfunc::Get ()->glAttachShader);
            load_gl_func ("glBindAttribLocation", Glfunc::Get ()->glBindAttribLocation);
            load_gl_func ("glLinkProgram", Glfunc::Get ()->glLinkProgram);
            load_gl_func ("glGetProgramiv", Glfunc::Get ()->glGetProgramiv);
            load_gl_func ("glGetProgramInfoLog", Glfunc::Get ()->glGetProgramInfoLog);
            load_gl_func ("glDeleteProgram", Glfunc::Get ()->glDeleteProgram);
            load_gl_func ("glUseProgram", Glfunc::Get ()->glUseProgram);
            load_gl_func ("glVertexAttribPointer", Glfunc::Get ()->glVertexAttribPointer);
            load_gl_func ("glEnableVertexAttribArray", Glfunc::Get ()->glEnableVertexAttribArray);
            load_gl_func ("glDisableVertexAttribArray", Glfunc::Get ()->glDisableVertexAttribArray);
            load_gl_func ("glGetUniformLocation", Glfunc::Get ()->glGetUniformLocation);
            load_gl_func ("glUniform1i", Glfunc::Get ()->glUniform1i);
            load_gl_func ("glActiveTexture", Glfunc::Get ()->glActiveTexture_);
            load_gl_func ("glUniform4fv", Glfunc::Get ()->glUniform4fv);
            load_gl_func ("glUniformMatrix3fv", Glfunc::Get ()->glUniformMatrix3fv);
        }
        catch (std::exception& ex)
        {
            std::cerr << ex.what ();
            return false;
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
        shader00->set_uniform ("u_color", Color (1.f, 0.f, 0.f, 1.f));

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
}
