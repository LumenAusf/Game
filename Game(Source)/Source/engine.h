#pragma once

#ifndef ENGINE_H
#define ENGINE_H

#include <tuple>

#include "event.h"
#include "gameobject.h"
#include "meshrenderer.h"
#include "texture.h"
#include "triangle.h"

namespace LumenAusf
{
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
        Texture* CreateTexture (std::string_view path, int hCount = 1, int wCount = 1);
        void DestroyTexture (Texture* t);
        void DrawTriangle (const tri0& t, const Color& c);
        void DrawTriangle (const tri1& t);
        void DrawTriangle (const tri2& t, Texture* tex);
        void DrawTriangle (const tri2& t, Texture* tex, const mat2x3& m);
        float getTimeFromInit ();
        void SwapBuffers ();
        void Clear ();

        Event EngineEvent = Event ();
    };
}
#endif    // ENGINE_H
