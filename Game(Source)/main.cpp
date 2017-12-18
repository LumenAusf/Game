#include <fstream>
#include <iostream>

#include "Source/engine.h"
#include "src/audio.h"

class Play
{
   public:
    float speed = 0.03f;
    int windowHeight = 480;
    int windowWidth = 640;

    void Run ()
    {
        try
        {
            Engine = new LumenAusf::Engine ();
            running = true;
            Engine->Init (false, windowWidth, windowHeight);

            initAudio ();
            Audio* music = createAudio ("music/Believer.wav", 1, SDL_MIX_MAXVOLUME);
            playMusicFromMemory (music, SDL_MIX_MAXVOLUME / 10);

            soundUp = createAudio ("sounds/no-1.wav", 0, SDL_MIX_MAXVOLUME);
            soundLeft = createAudio ("sounds/no-2.wav", 0, SDL_MIX_MAXVOLUME);
            soundDown = createAudio ("sounds/no-3.wav", 0, SDL_MIX_MAXVOLUME);
            soundRight = createAudio ("sounds/no-4.wav", 0, SDL_MIX_MAXVOLUME);

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
                        if (goTank->arrows != LumenAusf::Arrows::Down)
                        {
                            goTank->arrows = LumenAusf::Arrows::Down;
                            goTank->transform.rotation = LumenAusf::mat2x3::rotation (3.14f);
                        }
                        playSoundFromMemory (soundDown, SDL_MIX_MAXVOLUME);
                        break;
                    case LumenAusf::KEY_CODE::RIGHT:
                        std::clog << "RIGHT" << std::endl;
                        goTank->transform.position = goTank->transform.position * LumenAusf::mat2x3::move (LumenAusf::vec2 (speed, 0.f));
                        if (goTank->arrows != LumenAusf::Arrows::Right)
                        {
                            goTank->arrows = LumenAusf::Arrows::Right;
                            goTank->transform.rotation = LumenAusf::mat2x3::rotation (1.57f);
                        }
                        playSoundFromMemory (soundRight, SDL_MIX_MAXVOLUME);
                        break;
                    case LumenAusf::KEY_CODE::UP:
                        std::clog << "UP" << std::endl;
                        goTank->transform.position = goTank->transform.position * LumenAusf::mat2x3::move (LumenAusf::vec2 (0.f, speed));
                        if (goTank->arrows != LumenAusf::Arrows::Up)
                        {
                            goTank->arrows = LumenAusf::Arrows::Up;
                            goTank->transform.rotation = LumenAusf::mat2x3::rotation (0);
                        }
                        playSoundFromMemory (soundUp, SDL_MIX_MAXVOLUME);
                        break;
                    case LumenAusf::KEY_CODE::LEFT:
                        std::clog << "LEFT" << std::endl;
                        goTank->transform.position = goTank->transform.position * LumenAusf::mat2x3::move (LumenAusf::vec2 (-speed, 0.f));
                        if (goTank->arrows != LumenAusf::Arrows::Left)
                        {
                            goTank->arrows = LumenAusf::Arrows::Left;
                            goTank->transform.rotation = LumenAusf::mat2x3::rotation (3.14f + 1.57f);
                        }
                        playSoundFromMemory (soundLeft, SDL_MIX_MAXVOLUME);
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
    LumenAusf::Texture* textureGrass;
    LumenAusf::Texture* textureTank;
    LumenAusf::GameObject* goTank;
    Audio* soundUp;       //= createAudio("sounds/door1.wav", 0, SDL_MIX_MAXVOLUME / 2);
    Audio* soundLeft;     //= createAudio("sounds/door1.wav", 0, SDL_MIX_MAXVOLUME / 2);
    Audio* soundRight;    //= createAudio("sounds/door1.wav", 0, SDL_MIX_MAXVOLUME / 2);
    Audio* soundDown;     //= createAudio("sounds/door1.wav", 0, SDL_MIX_MAXVOLUME / 2);

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
    void RenderGameObject (LumenAusf::GameObject* go)
    {
        if (go == nullptr || go->triangles.size () == 0)
            return;

        for (unsigned long i = 0; i < go->triangles.size (); i++)
        {
            Engine->DrawTriangle (go->triangles.at (i), go->texture, go->transform.GetMatrix ());
        }
    }
    LumenAusf::GameObject* LoadGameObject (std::string TrianglesPath, LumenAusf::Texture* texture, int TrianglesCount)
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

        auto a = new LumenAusf::Transform;
        a->aspect.col0.x = 1;
        a->aspect.col0.y = 0.f;
        a->aspect.col1.x = 0.f;
        a->aspect.col1.y = 640.f / 480.f;

        auto go = new LumenAusf::GameObject (*a, triangles, texture);
        return go;
    }
};

int main ()
{
    Play game = Play ();
    game.Run ();
    return EXIT_SUCCESS;
}
