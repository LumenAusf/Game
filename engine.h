#ifndef ENGINE_H
#define ENGINE_H

#include <SDL2/SDL.h>
#include <string>
#include <iostream>
#include "DelegateAndEvent/event.h"
#include "DelegateAndEvent/eventitem.h"

namespace lumenausf
{
    class Engine
    {
        public:
            Engine();
            ~Engine();
            void Init(bool versionCritical = false, int width = 640, int height = 480, std::string windowName = "Engine");
            void ReadEvent();
            void Finish();

            Event EngineEvent = Event();
        private:
            bool CheckVersion();

            SDL_Window *window;
            bool running;
    };
}
#endif // ENGINE_H
