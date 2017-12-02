#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <string>

#include "event.h"

namespace LumenAusf
{
    struct vertex
    {
        vertex () : x (0.f), y (0.f) {}
        float x;
        float y;
    };

    struct triangle
    {
        triangle ()
        {
            v[0] = vertex ();
            v[1] = vertex ();
            v[2] = vertex ();
        }
        vertex v[3];
    };

    enum TYPE_EVENT
    {
        TYPENONE,

        QUIT,

        // Keyboard
        KEYDOWN,
        KEYUP,
        TEXTEDITING,
        TEXTINPUT,
        KEYMAPCHANGED,

        // Mouse
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
        SPACE
    };

    class EventItem
    {
       public:
        EventItem () {}
        ~EventItem () {}

        void Test () { std::clog << "Hop" << std::endl; }

        TYPE_EVENT typeEvent = TYPENONE;
        KEY_CODE keyCode = KEYNONE;
    };

    class Engine
    {
       public:
        Engine ();
        ~Engine ();
        void Init (bool versionCritical = false, int width = 640, int height = 480, std::string windowName = "Engine");
        void ReadEvent ();
        void Finish ();
        bool DrawTriangle (const triangle& t);

        Event EngineEvent = Event ();
    };
}
std::istream& operator>> (std::istream& is, LumenAusf::vertex&);
std::istream& operator>> (std::istream& is, LumenAusf::triangle&);
#endif    // ENGINE_H
