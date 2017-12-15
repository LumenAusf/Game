#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <string>
#include <vector>

#include "event.h"

namespace LumenAusf
{
    struct vec2
    {
        vec2 ();
        vec2 (float x, float y);
        float x = 0;
        float y = 0;
    };

    vec2 operator+ (const vec2& l, const vec2& r);

    struct mat2x3
    {
        mat2x3 ();
        static mat2x3 identity ();
        static mat2x3 scale (float scale);
        static mat2x3 rotation (float angle);
        static mat2x3 move (const vec2& delta);
        vec2 col0;
        vec2 col1;
        vec2 delta;
    };

    vec2 operator* (const vec2& v, const mat2x3& m);
    mat2x3 operator* (const mat2x3& m1, const mat2x3& m2);

    class color
    {
       public:
        color () = default;
        explicit color (std::uint32_t rgba_);
        color (float r, float g, float b, float a);

        float get_r () const;
        float get_g () const;
        float get_b () const;
        float get_a () const;

        void set_r (const float r);
        void set_g (const float g);
        void set_b (const float b);
        void set_a (const float a);

       private:
        std::uint32_t rgba = 0;
    };

    /// vertex with position only
    struct v0
    {
        vec2 pos;
    };

    /// vertex with position and texture coordinate
    struct v1
    {
        vec2 pos;
        color c;
    };

    /// vertex position + color + texture coordinate
    struct v2
    {
        vec2 pos;
        vec2 uv;
        color c;
    };

    /// triangle with positions only
    struct tri0
    {
        tri0 ();
        v0 v[3];
    };

    /// triangle with positions and color
    struct tri1
    {
        tri1 ();
        v1 v[3];
    };

    /// triangle with positions color and texture coordinate
    struct tri2
    {
        tri2 ();
        v2 v[3];
    };

    //    v0 blend (const v0& vl, const v0& vr, const float a)
    //    {
    //        v0 r;
    //        r.pos.x = (1.0f - a) * vl.pos.x + a * vr.pos.x;
    //        r.pos.y = (1.0f - a) * vl.pos.y + a * vr.pos.y;
    //        return r;
    //    }

    //    tri0 blend (const tri0& tl, const tri0& tr, const float a)
    //    {
    //        tri0 r;
    //        r.v[0] = blend (tl.v[0], tr.v[0], a);
    //        r.v[1] = blend (tl.v[1], tr.v[1], a);
    //        r.v[2] = blend (tl.v[2], tr.v[2], a);
    //        return r;
    //    }

    std::istream& operator>> (std::istream& is, mat2x3&);
    std::istream& operator>> (std::istream& is, vec2&);
    std::istream& operator>> (std::istream& is, color&);
    std::istream& operator>> (std::istream& is, v0&);
    std::istream& operator>> (std::istream& is, v1&);
    std::istream& operator>> (std::istream& is, v2&);
    std::istream& operator>> (std::istream& is, tri0&);
    std::istream& operator>> (std::istream& is, tri1&);
    std::istream& operator>> (std::istream& is, tri2&);

    class texture
    {
       public:
        virtual ~texture ();
        virtual std::uint32_t get_width () const = 0;
        virtual std::uint32_t get_height () const = 0;
    };

    class transformT
    {
       public:
        mat2x3 scale;
        mat2x3 rotation;
        mat2x3 position;
        mat2x3 aspect;

        mat2x3 GetMatrix () { return scale * rotation * position * aspect; }
    };

    enum Arrows
    {
        Up,
        Right,
        Down,
        Left
    };
    class gameObject
    {
       public:
        Arrows ar;
        texture* textureValue;
        transformT transform;
        std::vector<tri2> triangles;
        gameObject () {}
        gameObject (transformT a, std::vector<tri2> b, texture* c)
        {
            transform = a;
            triangles = b;
            textureValue = c;
        }
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
        texture* CreateTexture (std::string_view path);
        void DestroyTexture (texture* t);
        //        bool DrawTriangle (const triangle& t);
        void DrawTriangle (const tri0& t, const color& c);
        void DrawTriangle (const tri1& t);
        void DrawTriangle (const tri2& t, texture* tex);
        void DrawTriangle (const tri2& t, texture* tex, const mat2x3& m);
        float getTimeFromInit ();
        void SwapBuffers ();
        void Clear ();

        Event EngineEvent = Event ();
    };
}
#endif    // ENGINE_H
