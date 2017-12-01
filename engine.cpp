#include <SDL2/SDL.h> // Библиотека SDL 2
#include <iostream>
#include <cstdio>
#include "engine.h"

lumenausf::Engine::Engine()
{
    std::clog << "Create Engine" << std::endl;
}

lumenausf::Engine::~Engine()
{
    std::clog << "Destroy Engine" << std::endl;
}

void lumenausf::Engine::Init(bool versionCritical, int width, int height, std::string windowName)
{
    auto checkVersion = CheckVersion();
    if(!checkVersion)
    {
        if(versionCritical)
        {
            std::cerr << "FAILURE in CheckVersion: version.compiled != version.linked" << std::endl;
            exit(EXIT_FAILURE);
        }
        else
            std::clog << "WARNING in CheckVersion: version.compiled != version.linked" << std::endl;
    }
    else
    {
        std::clog << "SUCCES in CheckVersion" << std::endl;
    }

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "FAILURE in Init : Unable to init SDL, error: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    } else
    {
        std::clog << "SUCCES in Init : Init SDL" << std::endl;
    }

    auto window = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    if(window == nullptr)
    {
        std::cerr << "FAILURE in Init : Unable to create window, error: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    } else
    {
        std::clog << "SUCCES in Init : Create Window" << std::endl;
    }
}

bool lumenausf::Engine::CheckVersion()
{
    SDL_version compiled = {0, 0, 0};
    SDL_version linked = {0, 0, 0};

    SDL_VERSION(&compiled);
    SDL_GetVersion(&linked);

    auto result = compiled.major == linked.major &&
                  compiled.minor == linked.minor &&
                  compiled.patch == linked.patch;

    return result;
}

void lumenausf::Engine::ReadEvent()
{
    EventItem * event = new EventItem();
    SDL_Event eventSDL; // события SDL

    while(SDL_PollEvent(&eventSDL))
    {
        switch(eventSDL.type)
        {
            case SDL_QUIT:
                event->typeEvent = TYPE_EVENT::QUIT;
                EngineEvent(event);
            break;

            case SDL_KEYDOWN:
                event->typeEvent = TYPE_EVENT::KEYDOWN;
                switch(eventSDL.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        event->keyCode = KEY_CODE::ESCAPE;
                        EngineEvent(event);
                    break;
                    case SDLK_RETURN:
                        EngineEvent(new EventItem);
                    break;
                    case SDLK_UP:
                        event->keyCode = KEY_CODE::UP;
                        EngineEvent(event);
                    break;
                    case SDLK_LEFT:
                        event->keyCode = KEY_CODE::LEFT;
                        EngineEvent(event);
                    break;
                    case SDLK_DOWN:
                        event->keyCode = KEY_CODE::DOWN;
                        EngineEvent(event);
                    break;
                    case SDLK_RIGHT:
                        event->keyCode = KEY_CODE::RIGHT;
                        EngineEvent(event);
                    break;
                }
            break;
        }
    }
}

void lumenausf::Engine::Finish()
{
    this->~Engine();
}
