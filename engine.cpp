#include "engine.h"
#include <SDL2/SDL_version.h>
#include <iostream>
#include <cstdio>

using namespace lumenausf;

Engine::Engine()
{

}

void Engine::Init(bool versionCritical)
{
    auto checkVersion = CheckVersion();
    if(!checkVersion)
    {
        if(versionCritical)
        {
            std::cerr << "FAILURE in CheckVersion: version.compiled != version.linked" << std::endl;
            return;
        }
        else
            std::clog << "WARNING in CheckVersion: version.compiled != version.linked" << std::endl;
    }
    else
    {
        std::clog << "SUCCES in CheckVersion" << std::endl;
    }
}

bool Engine::CheckVersion()
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
