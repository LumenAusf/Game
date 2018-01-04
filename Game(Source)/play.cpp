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

    CreateBlock ("configurations/BlocksData.txt");

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
    Engine->setTimePrevious (Engine->getTimeFromInit (false));

    while (running)
    {
        if ((Engine->getTimeFromInit (false) - Engine->getTimePrevious ()) / 180.f * 1000 < 1)
            continue;

        LumenAusf::GameObject::UpdateAll ();
        LumenAusf::GameObject::FixedUpdateAll ();
        Engine->ReadEvent ();

        DrawGrass ();

        RenderAll ();

        //        RenderGameObject (goTank->go);
        //        RenderGameObject (goTank2->go);

        Engine->SwapBuffers ();
        Engine->setTimePrevious (Engine->getTimeFromInit (false));
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
        if (b == nullptr || !b->getEnabled ())
            continue;

        RenderGameObject (ob);
    }
}

struct BlockData
{
    int trianglesCount;
    std::vector<LumenAusf::tri2> triangles;
    LumenAusf::vec2 pos;
    int atlasWAll;
    int atlasHAll;
    int atlasStart;
    int atlasEnd;
    float atlasOffsetX;
    float atlasOffsetY;
    float scale;
};
std::istream& operator>> (std::istream& is, BlockData& t)
{
    is >> t.trianglesCount;
    for (auto i = 0; i < t.trianglesCount; i++)
    {
        LumenAusf::tri2 triangle;
        is >> triangle;
        t.triangles.push_back (triangle);
    }
    is >> t.pos;
    is >> t.atlasWAll;
    is >> t.atlasHAll;
    is >> t.atlasStart;
    is >> t.atlasEnd;
    is >> t.atlasOffsetX;
    is >> t.atlasOffsetY;
    is >> t.scale;
    return is;
}

void Play::CreateBlock (std::string configBlocks)
{
    static int num = 0;
    auto go = new LumenAusf::GameObject ("Block " + std::to_string (num++));
    go->tag = "Block";

    std::ifstream fd (configBlocks);
    if (!fd.is_open ())
    {
        go->~GameObject ();
        std::cerr << "Can`t open : " + configBlocks << std::endl;
        return;
    }

    auto td = BlockData ();
    fd >> td;
    fd.close ();
    go->transform->SetPosition (td.pos);
    go->transform->setLocalScale (LumenAusf::mat2x3::scale (td.scale));

    auto a = new LumenAusf::mat2x3 ();
    a->col0.x = 1;
    a->col0.y = 0.f;
    a->col1.x = 0.f;
    a->col1.y = static_cast<float> (windowWidth) / windowHeight;

    go->transform->setAspect (*a);

    go->AddComponent<LumenAusf::Collider> ();

    auto mr = go->AddComponent<LumenAusf::MeshRenderer> ();
    mr->offsetX = td.atlasOffsetX;
    mr->offsetY = td.atlasOffsetY;
    mr->meshType = LumenAusf::TypeOfMesh::Dynamic;
    mr->triangles = mr->trianglesOriginals = td.triangles;
    mr->texture = AtlasTank;
    mr->atlas = new LumenAusf::Atlas (mr);

    mr->SetAtlas (LumenAusf::vec2 (td.atlasWAll, td.atlasHAll), LumenAusf::vec2 (td.atlasStart, td.atlasEnd));
    //    mr->ResizeUV (LumenAusf::vec2 (1.f / (td.atlasWAll * 2.5f), 1.f / (td.atlasWAll * 2.5f)),
    //                  LumenAusf::vec2 (1.f / (td.atlasHAll * 2.5f), 1.f / (td.atlasHAll * 2.5f)));
}
