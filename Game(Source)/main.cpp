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
    float speed = 0.03f;
    void Run ()
    {
        try
        {
            Engine = new LumenAusf::Engine ();
            running = true;
            Engine->Init ();

            if (!LoadTextures ())
                return;

            goTank = LoadGameObject ("configurations/TankData.txt", textureTank, 2);
            goTank->transform.scale = LumenAusf::mat2x3::scale (0.5f);

            Engine->EngineEvent += Delegate (this, &Play::EventGetted);
            while (running)
            {
                Engine->ReadEvent ();

                DrawGrass ();

                RenderGameObject (goTank);

                Engine->SwapBuffers ();
            }
            Engine->DestroyTexture (textureTank);
            Engine->DestroyTexture (textureGrass);
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
                        goTank->transform.position = goTank->transform.position * LumenAusf::mat2x3::move (LumenAusf::vec2 (0.f, -speed));
                        if (goTank->ar != LumenAusf::Arrows::Down)
                        {
                            goTank->ar = LumenAusf::Arrows::Down;
                            goTank->transform.rotation = LumenAusf::mat2x3::rotation (3.14f);
                        }
                        break;
                    case LumenAusf::KEY_CODE::RIGHT:
                        std::clog << "RIGHT" << std::endl;
                        goTank->transform.position = goTank->transform.position * LumenAusf::mat2x3::move (LumenAusf::vec2 (speed, 0.f));
                        if (goTank->ar != LumenAusf::Arrows::Right)
                        {
                            goTank->ar = LumenAusf::Arrows::Right;
                            goTank->transform.rotation = LumenAusf::mat2x3::rotation (1.57f);
                        }
                        break;
                    case LumenAusf::KEY_CODE::UP:
                        std::clog << "UP" << std::endl;
                        goTank->transform.position = goTank->transform.position * LumenAusf::mat2x3::move (LumenAusf::vec2 (0.f, speed));
                        if (goTank->ar != LumenAusf::Arrows::Up)
                        {
                            goTank->ar = LumenAusf::Arrows::Up;
                            goTank->transform.rotation = LumenAusf::mat2x3::rotation (0);
                        }
                        break;
                    case LumenAusf::KEY_CODE::LEFT:
                        std::clog << "LEFT" << std::endl;
                        goTank->transform.position = goTank->transform.position * LumenAusf::mat2x3::move (LumenAusf::vec2 (-speed, 0.f));
                        if (goTank->ar != LumenAusf::Arrows::Left)
                        {
                            goTank->ar = LumenAusf::Arrows::Left;
                            goTank->transform.rotation = LumenAusf::mat2x3::rotation (3.14f + 1.57f);
                        }
                        break;
                    case LumenAusf::KEY_CODE::SPACE:

                        break;
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
    LumenAusf::texture* textureGrass;
    LumenAusf::texture* textureTank;
    LumenAusf::gameObject* goTank;

    void DrawGrass ()
    {
        std::ifstream fileGrass ("configurations/GrassData.txt");
        assert (!!fileGrass);
        LumenAusf::tri2 tr1Grass;
        LumenAusf::tri2 tr2Grass;
        fileGrass >> tr1Grass >> tr2Grass;
        LumenAusf::mat2x3 aspectlocal;

        Engine->DrawTriangle (tr1Grass, textureGrass, aspectlocal);
        Engine->DrawTriangle (tr2Grass, textureGrass, aspectlocal);
    }
    bool LoadTextures ()
    {
        textureGrass = Engine->CreateTexture ("textures/grass.png");
        if (nullptr == textureGrass)
        {
            std::cerr << "Can`t Load Texture GRASS" << std::endl;
            return false;
        }

        textureTank = Engine->CreateTexture ("textures/tank.png");
        if (nullptr == textureTank)
        {
            std::cerr << "Can`t Load Texture TANK" << std::endl;
            return false;
        }

        return true;
    }
    void RenderGameObject (LumenAusf::gameObject* go)
    {
        if (go == nullptr || go->triangles.size () == 0)
            return;

        for (unsigned long i = 0; i < go->triangles.size (); i++)
        {
            Engine->DrawTriangle (go->triangles.at (i), go->textureValue, go->transform.GetMatrix ());
        }
    }
    LumenAusf::gameObject* LoadGameObject (std::string TrianglesPath, LumenAusf::texture* texture, int TrianglesCount)
    {
        std::ifstream fileTriangles (TrianglesPath);
        if (!fileTriangles.is_open ())
            return nullptr;

        std::vector<LumenAusf::tri2> triangles;

        for (auto i = 0; i < TrianglesCount; i++)
        {
            LumenAusf::tri2 triangle;
            fileTriangles >> triangle;
            triangles.push_back (triangle);
        }

        auto a = new LumenAusf::transformT;
        a->aspect.col0.x = 1;
        a->aspect.col0.y = 0.f;
        a->aspect.col1.x = 0.f;
        a->aspect.col1.y = 640.f / 480.f;

        auto go = new LumenAusf::gameObject (*a, triangles, texture);
        return go;
    }
};

int main ()
{
    Play game = Play ();
    game.Run ();
    return EXIT_SUCCESS;
}
