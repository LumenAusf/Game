#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <memory>
#include <string_view>

#include "Source/engine.h"

LumenAusf::v0 Lerp (const LumenAusf::v0& vl, const LumenAusf::v0& vr, const float a)
{
    LumenAusf::v0 r;
    r.pos.x = (1.0f - a) * vl.pos.x + a * vr.pos.x;
    r.pos.y = (1.0f - a) * vl.pos.y + a * vr.pos.y;
    return r;
}

LumenAusf::tri0 Lerp (const LumenAusf::tri0& tl, const LumenAusf::tri0& tr, const float a)
{
    LumenAusf::tri0 r;
    r.v[0] = Lerp (tl.v[0], tr.v[0], a);
    r.v[1] = Lerp (tl.v[1], tr.v[1], a);
    r.v[2] = Lerp (tl.v[2], tr.v[2], a);
    return r;
}

class Play
{
   public:
    int current_shader = 0;
    void Run ()
    {
        try
        {
            Engine = new LumenAusf::Engine ();
            running = true;
            Engine->Init ();

            LumenAusf::texture* texture = Engine->CreateTexture ("textureWD.png");
            if (nullptr == texture)
            {
                std::cerr << "failed load texture\n";
                return;
            }

            Engine->EngineEvent += Delegate (this, &Play::EventGetted);
            while (running)
            {
                Engine->ReadEvent ();
                if (current_shader == 0)
                {
                    std::ifstream file ("vert_pos.txt");
                    assert (!!file);

                    LumenAusf::tri0 tr1;
                    LumenAusf::tri0 tr2;
                    LumenAusf::tri0 tr11;
                    LumenAusf::tri0 tr22;

                    file >> tr1 >> tr2 >> tr11 >> tr22;

                    float time = Engine->getTimeFromInit ();

                    auto a = Lerp (tr1, tr11, std::cos (time));
                    auto b = Lerp (tr2, tr22, std::cos (time));

                    LumenAusf::mat2x3 move = LumenAusf::mat2x3::move (LumenAusf::vec2 (std::sin (time), 0.f));

                    LumenAusf::mat2x3 aspect;
                    aspect.col0.x = 1;
                    aspect.col0.y = 0.f;
                    aspect.col1.x = 0.f;
                    aspect.col1.y = 640.f / 480.f;

                    LumenAusf::mat2x3 m = LumenAusf::mat2x3::rotation (std::sin (time)) * move * aspect;

                    for (auto& v : a.v)
                    {
                        v.pos = v.pos * m;
                    }
                    for (auto& v : b.v)
                    {
                        v.pos = v.pos * m;
                    }

                    Engine->DrawTriangle (a, LumenAusf::color (1.f, 0.f, 0.f, 1.f));
                    Engine->DrawTriangle (b, LumenAusf::color (0.f, 1.f, 0.f, 1.f));
                }

                if (current_shader == 1)
                {
                    std::ifstream file ("vert_pos_color.txt");
                    assert (!!file);

                    LumenAusf::tri1 tr1;
                    LumenAusf::tri1 tr2;

                    file >> tr1 >> tr2;

                    Engine->DrawTriangle (tr1);
                    Engine->DrawTriangle (tr2);
                }

                if (current_shader == 2)
                {
                    std::ifstream file ("vert_pos.txt");
                    assert (!!file);

                    LumenAusf::tri0 tr1;
                    LumenAusf::tri0 tr2;
                    LumenAusf::tri0 tr11;
                    LumenAusf::tri0 tr22;

                    file >> tr1 >> tr2 >> tr11 >> tr22;

                    float time = Engine->getTimeFromInit ();

                    auto a = Lerp (tr1, tr11, std::cos (time));
                    auto b = Lerp (tr2, tr22, std::cos (time));

                    Engine->DrawTriangle (a, LumenAusf::color (1.f, 0.f, 0.f, 1.f));
                    Engine->DrawTriangle (b, LumenAusf::color (0.f, 1.f, 0.f, 1.f));

                    //*-*-*-*-*-*-*-*-*-*-*-*-*
                    std::ifstream file1 ("vert_tex_color.txt");
                    assert (!!file1);

                    LumenAusf::tri2 tr1l;
                    LumenAusf::tri2 tr2l;

                    file1 >> tr1l >> tr2l;

                    //                    float time = Engine->getTimeFromInit ();
                    LumenAusf::mat2x3 move = LumenAusf::mat2x3::move (LumenAusf::vec2 (std::sin (time), 0.f));

                    LumenAusf::mat2x3 aspect;
                    aspect.col0.x = 1;
                    aspect.col0.y = 0.f;
                    aspect.col1.x = 0.f;
                    aspect.col1.y = 640.f / 480.f;

                    LumenAusf::mat2x3 m = LumenAusf::mat2x3::rotation (std::sin (time)) * move * aspect;

                    Engine->DrawTriangle (tr1l, texture, m);
                    Engine->DrawTriangle (tr2l, texture, m);
                }

                Engine->SwapBuffers ();
            }
            Engine->DestroyTexture (texture);
            Engine->Finish ();
        }
        catch (std::exception ex)
        {
            std::cerr << ex.what ();
            exit (EXIT_FAILURE);
        }
    }

    void EventGetted (LumenAusf::EventItem item)
    {
        switch (item.typeEvent)
        {
            case LumenAusf::TYPE_EVENT::KEYDOWN:
                switch (item.keyCode)
                {
                    case LumenAusf::KEY_CODE::ESCAPE:
                        running = false;
                        break;
                    case LumenAusf::KEY_CODE::DOWN:
                        std::clog << "DOWN" << std::endl;
                        break;
                    case LumenAusf::KEY_CODE::RIGHT:
                        std::clog << "RIGHT" << std::endl;
                        break;
                    case LumenAusf::KEY_CODE::UP:
                        std::clog << "UP" << std::endl;
                        break;
                    case LumenAusf::KEY_CODE::LEFT:
                        std::clog << "LEFT" << std::endl;
                        break;
                    case LumenAusf::KEY_CODE::SPACE:
                    {
                        ++current_shader;
                        if (current_shader > 2)
                        {
                            current_shader = 0;
                        }
                    }
                    default:
                        break;
                }
                break;
            case LumenAusf::TYPE_EVENT::QUIT:
                running = false;
                break;
            default:

                break;
        }
    }

   private:
    bool running;
    LumenAusf::Engine* Engine;
};

int main ()
{
    Play game = Play ();
    game.Run ();
    return EXIT_SUCCESS;
}
