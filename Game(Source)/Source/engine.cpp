#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_opengl_glext.h>
#include <cstdio>
#include <iostream>

#include "engine.h"

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

            glLoadIdentity ();

            auto r = ((float)std::rand ()) / RAND_MAX;
            auto g = ((float)std::rand ()) / RAND_MAX;
            auto b = ((float)std::rand ()) / RAND_MAX;

            glColor3f (r, g, b);

            glBegin (GL_TRIANGLES);                   // Начинаем рисовать треугольник
            glVertex3f (t.v[0].x, t.v[0].y, 0.0f);    // Top
            glVertex3f (t.v[1].x, t.v[1].y, 0.0f);    // Bottom Left
            glVertex3f (t.v[2].x, t.v[2].y, 0.0f);    // Bottom Right
            glEnd ();

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
