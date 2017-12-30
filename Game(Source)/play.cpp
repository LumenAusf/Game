#include "play.h"

void Play::Run ()
{
    Engine = new LumenAusf::Engine ();
    running = true;
    Engine->Init (false, windowWidth, windowHeight);

    initAudio ();
    Audio* music = createAudio ("music/Believer.wav", 1, SDL_MIX_MAXVOLUME);
    playSoundFromMemory (music, SDL_MIX_MAXVOLUME / 3);

    if (!LoadTextures ())
        return;

    goTank = InitTank (1, 8);
    goTank->go->transform->SetPosition (LumenAusf::vec2 (0.f, -0.5f));

    goTank2 = InitTank (9, 16, 1.5f);
    goTank2->go->transform->SetPosition (LumenAusf::vec2 (0.f, 0.5f));

    Engine->EngineEvent += Delegate (this, &Play::EventGetted);

    LumenAusf::GameObject::AwakeAll ();
    LumenAusf::GameObject::StartAll ();

    while (running)
    {
        LumenAusf::GameObject::UpdateAll ();
        LumenAusf::GameObject::FixedUpdateAll ();
        Engine->ReadEvent ();

        DrawGrass ();

        RenderGameObject (goTank->go);
        RenderGameObject (goTank2->go);

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

                case LumenAusf::KEY_CODE::DOWN:
                    std::clog << "DOWN" << std::endl;
                    goTank->Rotate (Arrows::Down);
                    goTank->Move ();

                    goTank2->Rotate (Arrows::Up);
                    goTank2->Move ();
                    break;

                case LumenAusf::KEY_CODE::RIGHT:
                    std::clog << "RIGHT" << std::endl;
                    goTank->Rotate (Arrows::Right);
                    goTank->Move ();

                    goTank2->Rotate (Arrows::Right);
                    goTank2->Move ();
                    break;

                case LumenAusf::KEY_CODE::UP:
                    std::clog << "UP" << std::endl;
                    goTank->Rotate (Arrows::Up);
                    goTank->Move ();

                    goTank2->Rotate (Arrows::Down);
                    goTank2->Move ();
                    break;

                case LumenAusf::KEY_CODE::LEFT:
                    std::clog << "LEFT" << std::endl;
                    goTank->Rotate (Arrows::Left);
                    goTank->Move ();

                    goTank2->Rotate (Arrows::Left);
                    goTank2->Move ();
                    break;

                case LumenAusf::KEY_CODE::SPACE:
                    playSound ("sounds/TankFire.wav", SDL_MIX_MAXVOLUME);
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

void Play::DrawGrass ()
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

bool Play::LoadTextures ()
{
    textureGrass = Engine->CreateTexture ("textures/grass.png");
    if (nullptr == textureGrass)
    {
        std::cerr << "Can`t Load Texture GRASS" << std::endl;
        return false;
    }

    AtlasTank = Engine->CreateTexture ("textures/TankAtlas.png");
    if (nullptr == AtlasTank)
    {
        std::cerr << "Can`t Load Atlas Texture TANK" << std::endl;
        return false;
    }

    return true;
}

Tank* Play::InitTank (int AtlasStart, int AtlasEnd, float offsetX, float offsetY)
{
    auto b = createAudio ("sounds/EngineStart.wav", 0, SDL_MIX_MAXVOLUME / 2);
    auto c = createAudio ("sounds/EngineAwake.wav", 1, SDL_MIX_MAXVOLUME / 2);
    auto d = createAudio ("sounds/EngineRun.wav", 0, SDL_MIX_MAXVOLUME / 2);
    auto e = createAudio ("sounds/TankFire.wav", 0, SDL_MIX_MAXVOLUME);

    auto go = CreateTank ("configurations/TankData.txt", AtlasTank, 2, AtlasStart, AtlasEnd, offsetX, offsetY);
    go->go->transform->setLocalScale (LumenAusf::mat2x3::scale (0.5f));
    go->SetSounds (b, c, d, e);
    go->setSpeed (speed);

    return go;
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

Tank* Play::CreateTank (std::string TrianglesPath, LumenAusf::Texture* texture, int TrianglesCount, int AtlasStart, int AtlasEnd, float offsetX,
                        float offsetY)
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

    auto a = new LumenAusf::mat2x3 ();
    a->col0.x = 1;
    a->col0.y = 0.f;
    a->col1.x = 0.f;
    a->col1.y = static_cast<float> (windowWidth) / windowHeight;

    auto go = new Tank (*a);

    // for test
    go->go->AddComponent<LumenAusf::Collider> ();

    auto b = go->go->AddComponent<LumenAusf::MeshRenderer> ();
    b->offsetX = offsetX;
    b->offsetY = offsetY;
    b->meshType = LumenAusf::TypeOfMesh::Dynamic;
    b->triangles = b->trianglesOriginals = triangles;
    b->texture = texture;
    b->atlas = new LumenAusf::Atlas (b);

    b->SetAtlas (LumenAusf::vec2 (8, 4), LumenAusf::vec2 (AtlasStart, AtlasEnd));
    return go;
}
