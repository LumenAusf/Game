#ifndef ENGINE_H
#define ENGINE_H

//#include <SDL2/SDL.h>
#include <string>
#include <iostream>
#include "DelegateAndEvent/event.h"
//#include "DelegateAndEvent/eventitem.h"

namespace lumenausf
{
    enum TYPE_EVENT
    {
        TYPENONE,

        QUIT,

        //Keyboard
        KEYDOWN,
        KEYUP,
        TEXTEDITING,
        TEXTINPUT,
        KEYMAPCHANGED,

        //Mouse
        MOUSEMOTION,
        MOUSEBUTTONDOWN,
        MOUSEBUTTONUP,
        MOUSEWHEEL,
    };

    enum KEY_CODE
    {
        KEYNONE,

        RIGHT,
        LEFT,
        DOWN,
        UP,
        ESCAPE,
    };

    class EventItem
    {
        public:
            EventItem(){}
            ~EventItem(){}
            void Test(){
                std::clog << "Hop" << std::endl;
            }

            TYPE_EVENT typeEvent = TYPENONE;
            KEY_CODE keyCode = KEYNONE;
    };

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
    };
}
#endif // ENGINE_H
