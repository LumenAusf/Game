#include "play.h"

void Play::Run ()
{
    Engine = new LumenAusf::Engine ();
    running = true;
    Engine->Init (false, windowWidth, windowHeight);

    initAudio ();
    Audio* music = createAudio ("music/Believer.wav", 1, SDL_MIX_MAXVOLUME / 10);
    playSoundFromMemory (music, SDL_MIX_MAXVOLUME / 3);

    if (!LoadTextures ())
        return;

    goTank = new Tank ("configurations/TankUserData.txt", AtlasTank, true);
    goTank->SetAspect (windowWidth, windowHeight);

    //    goTank2 = new Tank ("configurations/TankNPCData.txt", AtlasTank, false);
    //    goTank2->SetAspect (windowWidth, windowHeight);

    //    goTank3 = new Tank ("configurations/TankNPCData2.txt", AtlasTank, false);
    //    goTank3->SetAspect (windowWidth, windowHeight);

    //    goTank4
    //        = new Tank ("configurations/TankNPCData3.txt", AtlasTank, false);
    //        goTank4
    //            ->SetAspect (windowWidth, windowHeight);

    //            goTank5 = new Tank ("configurations/TankNPCData4.txt", AtlasTank, false);
    //            goTank5->SetAspect (windowWidth, windowHeight);
    //    goTank2 = InitTank (9, 16, 1.5f);
    //    goTank2->go->transform->SetPosition (LumenAusf::vec2 (0.f, 0.5f));

    Engine->EngineEvent += Delegate (this, &Play::EventGetted);

    LumenAusf::GameObject::AwakeAll ();
    LumenAusf::GameObject::StartAll ();

    while (running)
    {
        LumenAusf::GameObject::UpdateAll ();
        LumenAusf::GameObject::FixedUpdateAll ();
        Engine->ReadEvent ();

        DrawGrass ();

        RenderAll ();

        //        RenderGameObject (goTank->go);
        //        RenderGameObject (goTank2->go);

        Engine->SwapBuffers ();
    }
    Engine->DestroyTexture (AtlasTank);
    Engine->DestroyTexture (textureGrass);
    Engine->Finish ();
}

void Play::EventGetted (LumenAusf::EventItem item)
{
    switch (item.typeEvent)
    {
        case LumenAusf::TYPE_EVENT::KEYDOWN:
            switch (item.keyCode)
            {
                case LumenAusf::KEY_CODE::ESCAPE:
                    running = false;
                    break;

                //                case LumenAusf::KEY_CODE::DOWN:
                //                    std::clog << "DOWN" << std::endl;
                //                    goTank->Rotate (Arrows::Down);
                //                    goTank->Move ();

                //                    goTank2->Rotate (Arrows::Up);
                //                    goTank2->Move ();
                //                    break;

                //                case LumenAusf::KEY_CODE::RIGHT:
                //                    std::clog << "RIGHT" << std::endl;
                //                    goTank->Rotate (Arrows::Right);
                //                    goTank->Move ();

                //                    goTank2->Rotate (Arrows::Right);
                //                    goTank2->Move ();
                //                    break;

                //                case LumenAusf::KEY_CODE::UP:
                //                    std::clog << "UP" << std::endl;
                //                    goTank->Rotate (Arrows::Up);
                //                    goTank->Move ();

                //                    goTank2->Rotate (Arrows::Down);
                //                    goTank2->Move ();
                //                    break;

                //                case LumenAusf::KEY_CODE::LEFT:
                //                    std::clog << "LEFT" << std::endl;
                //                    goTank->Rotate (Arrows::Left);
                //                    goTank->Move ();

                //                    goTank2->Rotate (Arrows::Left);
                //                    goTank2->Move ();
                //                    break;

                //                case LumenAusf::KEY_CODE::SPACE:
                //                    goTank->Fire ();
                //                    playSound ("sounds/TankFire.wav", SDL_MIX_MAXVOLUME);
                //                    break;
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

void Play::DrawGrass ()
{
    std::ifstream fileGrass ("configurations/GrassData.txt");
    assert (!!fileGrass);
    LumenAusf::tri2 tr1Grass;
    LumenAusf::tri2 tr2Grass;
    fileGrass >> tr1Grass >> tr2Grass;

    Engine->DrawTriangle (tr1Grass, textureGrass, LumenAusf::mat2x3 ());
    Engine->DrawTriangle (tr2Grass, textureGrass, LumenAusf::mat2x3 ());
}

bool Play::LoadTextures ()
{
    textureGrass = Engine->CreateTexture ("textures/grass.png");
    if (nullptr == textureGrass)
    {
        std::cerr << "Can`t Load Texture GRASS" << std::endl;
        return false;
    }

    AtlasTank = Engine->CreateTexture ("textures/TankAtlasTest.png");
    if (nullptr == AtlasTank)
    {
        std::cerr << "Can`t Load Atlas Texture TANK" << std::endl;
        return false;
    }

    return true;
}

void Play::RenderGameObject (LumenAusf::GameObject* go)
{
    if (go == nullptr)
        return;

    auto b = go->GetComponent<LumenAusf::MeshRenderer> ();
    if (b == nullptr)
        return;

    if (b->triangles.size () == 0)
        return;

    for (unsigned long i = 0; i < b->triangles.size (); i++)
    {
        Engine->DrawTriangle (b->triangles.at (i), b->texture, go->transform->GetGlobalMatrix ());
    }
}

void Play::RenderAll ()
{
    for (auto ob : LumenAusf::GameObject::objects)
    {
        if (!ob->enabled)
            continue;

        auto b = ob->GetComponent<LumenAusf::MeshRenderer> ();
        if (ob == nullptr || !ob->enabled)
            continue;

        RenderGameObject (ob);
    }
}
