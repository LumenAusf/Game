#include "play.h"

LumenAusf::Engine* Play::Engine = nullptr;

void Play::Run ()
{
    Engine = new LumenAusf::Engine ();
    int previousFPS = 0;
    running = true;
    Engine->Init (false, windowWidth, windowHeight);

    std::srand (unsigned(std::time (0)));

    initAudio ();
    Audio* music = createAudio ("music/Believer.wav", 1, SDL_MIX_MAXVOLUME / 10);
    playSoundFromMemory (music, SDL_MIX_MAXVOLUME / 3);

    if (!LoadTextures ())
        return;

    InitScene ("configurations/MapData.txt", "configurations/BlocksData.txt", "configurations/TankUserData.txt", "configurations/TankNPCData.txt",
               "configurations/EagleData.txt", "configurations/MissileData.txt");
    //    goTank = new Tank ("configurations/TankUserData.txt", AtlasTank, true, &running);
    //    goTank->SetAspect (windowWidth, windowHeight);

    //    CreateBlocks ("configurations/BlocksData.txt", "configurations/MapData.txt");
    //    CreateEagle ("configurations/EagleData.txt");

    //    goTank2 = new Tank ("configurations/TankNPCData.txt", AtlasTank, false, nullptr);
    //    goTank2->SetAspect (windowWidth, windowHeight);

    //    goTank3 = new Tank ("configurations/TankNPCData2.txt", AtlasTank, false);
    //    goTank3->SetAspect (windowWidth, windowHeight);

    //    goTank4
    //        = new Tank ("configurations/TankNPCData3.txt", AtlasTank, false);
    //        goTank4
    //            ->SetAspect (windowWidth, windowHeight);

    //            goTank5 = new Tank ("configurations/TankNPCData4.txt", AtlasTank, false);
    //            goTank5->SetAspect (windowWidth, windowHeight);

    Engine->EngineEvent += Delegate (this, &Play::EventGetted);

    LumenAusf::GameObject::AwakeAll ();
    LumenAusf::GameObject::StartAll ();
    Engine->setTimePrevious (Engine->getTimeFromInit (false));

    while (running)
    {
        if ((Engine->getTimeFromInit (false) - Engine->getTimePrevious ()) / 1000.f < 1.f / 180.f)
            continue;
        auto a = Engine->getTimeFromInit (false);

        auto currentFPS = static_cast<int> (1.f / ((Engine->getTimeFromInit (false) - Engine->getTimePrevious ()) / 1000.f));

        if (currentFPS != previousFPS)
        {
            std::clog << currentFPS << std::endl;
            previousFPS = currentFPS;
        }

        Engine->ReadEvent ();

        LumenAusf::GameObject::UpdateAll ();
        LumenAusf::GameObject::FixedUpdateAll ();

        Engine->setTimePrevious (a);

        DrawGrass ();
        RenderAll ();

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

LumenAusf::Engine* Play::getEngine () { return Engine; }

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
        if (ob == nullptr || !ob->enabled)
            continue;

        auto b = ob->GetComponent<LumenAusf::MeshRenderer> ();
        if (b == nullptr || !b->getEnabled ())
            continue;

        RenderGameObject (ob);
    }
}

// struct ObjectConfig
//{
//    int atlasWAll;
//    int atlasHAll;
//    int atlasStart;
//    int atlasEnd;
//    float atlasOffsetX;
//    float atlasOffsetY;
//    float scale;
//};
std::istream& operator>> (std::istream& is, ObjectConfig& t)
{
    is >> t.atlasWAll;
    is >> t.atlasHAll;
    is >> t.atlasStart;
    is >> t.atlasEnd;
    is >> t.atlasOffsetX;
    is >> t.atlasOffsetY;
    is >> t.scale;
    return is;
}

// void CreateBlock (ObjectConfig data, int number);
// void CreateEagle (ObjectConfig data, int number);
// void CreateTank (ObjectConfig data, int number, std::vector<std::string> audioTank, std::vector<std::string> audioMissile, bool isUser);

void Play::InitScene (std::string configMap, std::string configBlocks, std::string configTank, std::string configNpcTank, std::string configEagle,
                      std::string configMissile)
{
    auto blockData = ObjectConfig ();
    auto missileData = ObjectConfig ();
    auto tankData = ObjectConfig ();
    auto tankNPCData = ObjectConfig ();
    auto eagleData = ObjectConfig ();
    std::vector<std::string> audioTank;
    std::vector<std::string> audioMissile;

    // Read map
    std::ifstream md (configMap);
    if (!md.is_open ())
    {
        std::cerr << "Can`t open : " + configMap << std::endl;
        return;
    }

    std::vector<int> map;
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 8; j++)
        {
            int k;
            md >> k;
            map.push_back (k);
        }

    // Load configurations
    // -Block
    std::ifstream File (configBlocks);
    if (!File.is_open ())
    {
        std::cerr << "Can`t open : " + configBlocks << std::endl;
        return;
    }

    File >> blockData;
    File.close ();

    // -Eagle
    File.open (configEagle);
    if (!File.is_open ())
    {
        std::cerr << "Can`t open : " + configEagle << std::endl;
        return;
    }

    File >> eagleData;
    File.close ();

    // -Tank
    File.open (configTank);
    if (!File.is_open ())
    {
        std::cerr << "Can`t open : " + configTank << std::endl;
        return;
    }

    std::string audioPathTankStart, audioPathTankAwake, audioPathTankRun, audioPathTankFire;
    File >> tankData >> audioPathTankStart >> audioPathTankAwake >> audioPathTankRun >> audioPathTankFire;

    audioTank.push_back (audioPathTankStart);
    audioTank.push_back (audioPathTankAwake);
    audioTank.push_back (audioPathTankRun);
    audioTank.push_back (audioPathTankFire);

    File.close ();

    // -NPCTank
    File.open (configNpcTank);
    if (!File.is_open ())
    {
        std::cerr << "Can`t open : " + configNpcTank << std::endl;
        return;
    }

    File >> tankNPCData;

    File.close ();

    // -Missile
    File.open (configMissile);
    if (!File.is_open ())
    {
        std::cerr << "Can`t open : " + configMissile << std::endl;
        return;
    }

    std::string audioPathMissileRun, audioPathMissileFire;
    File >> missileData >> audioPathMissileRun >> audioPathMissileFire;

    audioMissile.push_back (audioPathMissileRun);
    audioMissile.push_back (audioPathMissileFire);

    File.close ();

    // End of loading

    /*Creating objects
     * 0 - None
     * 1 - Block
     * 2 - Eagle
     * 3 - User
     * 4 - NPC
     */
    for (size_t number = 0; number < 48; number++)
    {
        if (map[number] == 0)
            continue;
        if (map[number] == 1)
            CreateBlock (blockData, static_cast<int> (number));
        if (map[number] == 2)
            CreateEagle (eagleData, static_cast<int> (number));
        if (map[number] == 3)
            CreateTank (tankData, static_cast<int> (number), audioTank, audioMissile, true);
        if (map[number] == 4)
            CreateTank (tankNPCData, static_cast<int> (number), audioTank, audioMissile, false);
    }
}

void Play::CreateBlock (ObjectConfig data, int number)
{
    static int num;
    auto go = new LumenAusf::GameObject ("Block " + std::to_string (num++));
    go->tag = "Block";
    go->transform->SetPosition (LumenAusf::vec2 (-1.f + data.scale + ((number % 8) * data.scale * 2), 0.5f - (number / 8) * data.scale * 2));
    go->transform->setLocalScale (LumenAusf::mat2x3::scale (data.scale));

    auto a = new LumenAusf::mat2x3 ();
    a->col0.x = 1;
    a->col0.y = 0.f;
    a->col1.x = 0.f;
    a->col1.y = static_cast<float> (windowWidth) / windowHeight;
    go->transform->setAspect (*a);

    go->AddComponent<LumenAusf::Collider> ();

    auto mr = go->AddComponent<LumenAusf::MeshRenderer> ();
    mr->offsetX = data.atlasOffsetX;
    mr->offsetY = data.atlasOffsetY;
    mr->meshType = LumenAusf::TypeOfMesh::Dynamic;
    mr->triangles = mr->trianglesOriginals = Engine->CreateQuadtc ();
    mr->texture = AtlasTank;
    mr->atlas = new LumenAusf::Atlas (mr);
    mr->SetAtlas (LumenAusf::vec2 (data.atlasWAll, data.atlasHAll), LumenAusf::vec2 (data.atlasStart, data.atlasEnd));
}

void Play::CreateTank (ObjectConfig data, int number, std::vector<std::string> audioTank, std::vector<std::string> audioMissile, bool isUser)
{
    static int num;
    auto tank = new LumenAusf::GameObject (nullptr);

    if (isUser)
    {
        tank->name = "UserTank";
        tank->tag = "TankUser";
    }
    else
    {
        tank->name = "NPCTank " + std::to_string (num++);
        tank->tag = "TankNPC";
    }

    tank->transform->SetPosition (LumenAusf::vec2 (-1.f + data.scale + ((number % 8) * data.scale * 2), 0.5f - (number / 8) * data.scale * 2));
    tank->transform->setLocalScale (LumenAusf::mat2x3::scale (data.scale));

    auto a = new LumenAusf::mat2x3 ();
    a->col0.x = 1;
    a->col0.y = 0.f;
    a->col1.x = 0.f;
    a->col1.y = static_cast<float> (windowWidth) / windowHeight;
    tank->transform->setAspect (*a);

    tank->AddComponent<LumenAusf::Collider> ();

    auto mr = tank->AddComponent<LumenAusf::MeshRenderer> ();
    mr->offsetX = data.atlasOffsetX;
    mr->offsetY = data.atlasOffsetY;
    mr->meshType = LumenAusf::TypeOfMesh::Dynamic;
    mr->triangles = mr->trianglesOriginals = Play::getEngine ()->CreateQuadtc ();
    mr->texture = AtlasTank;
    mr->atlas = new LumenAusf::Atlas (mr);

    mr->SetAtlas (LumenAusf::vec2 (data.atlasWAll, data.atlasHAll), LumenAusf::vec2 (data.atlasStart, data.atlasEnd));

    auto b = createAudio (audioTank[0].c_str (), 0, SDL_MIX_MAXVOLUME / 2);
    auto c = createAudio (audioTank[1].c_str (), 1, SDL_MIX_MAXVOLUME / 2);
    auto d = createAudio (audioTank[2].c_str (), 0, SDL_MIX_MAXVOLUME / 2);
    auto e = createAudio (audioTank[3].c_str (), 0, SDL_MIX_MAXVOLUME);

    if (isUser)
    {
        tank->AddComponent<GameOverController> ();
        auto tnc = tank->AddComponent<TankController> ();
        tnc->SetSounds (b, c, d, e);
        tnc->SetTextureMissile (AtlasTank);
    }
    else
    {
        auto tnc = tank->AddComponent<TankNPCController> ();
        tnc->SetSounds (b, c, d, e);
        tnc->SetTextureMissile (AtlasTank);
    }
}

// struct BlockData
//{
//    int atlasWAll;
//    int atlasHAll;
//    int atlasStart;
//    int atlasEnd;
//    float atlasOffsetX;
//    float atlasOffsetY;
//    float scale;
//};
// std::istream& operator>> (std::istream& is, BlockData& t)
//{
//    is >> t.atlasWAll;
//    is >> t.atlasHAll;
//    is >> t.atlasStart;
//    is >> t.atlasEnd;
//    is >> t.atlasOffsetX;
//    is >> t.atlasOffsetY;
//    is >> t.scale;
//    return is;
//}

// void Play::CreateBlocks (std::string configBlocks, std::string configMap)
//{
//    // todo: remake to InitScene with blocks,tanks and eagle

//    int num = 0;

//    std::ifstream bd (configBlocks);
//    if (!bd.is_open ())
//    {
//        std::cerr << "Can`t open : " + configBlocks << std::endl;
//        return;
//    }

//    auto td = BlockData ();
//    bd >> td;
//    bd.close ();

//    std::ifstream md (configMap);
//    if (!md.is_open ())
//    {
//        std::cerr << "Can`t open : " + configBlocks << std::endl;
//        return;
//    }

//    std::vector<int> map;
//    for (int i = 0; i < 6; i++)
//        for (int j = 0; j < 8; j++)
//        {
//            int k;
//            md >> k;
//            map.push_back (k);
//        }

//    for (size_t number = 0; number < 48; number++)
//    {
//        if (map[number] == 0)
//            continue;
//        auto go = new LumenAusf::GameObject ("Block " + std::to_string (num++));
//        go->tag = "Block";
//        go->transform->SetPosition (LumenAusf::vec2 (-1.f + td.scale + ((number % 8) * td.scale * 2), 0.5f - (number / 8) * td.scale * 2));
//        go->transform->setLocalScale (LumenAusf::mat2x3::scale (td.scale));

//        auto a = new LumenAusf::mat2x3 ();
//        a->col0.x = 1;
//        a->col0.y = 0.f;
//        a->col1.x = 0.f;
//        a->col1.y = static_cast<float> (windowWidth) / windowHeight;
//        go->transform->setAspect (*a);

//        go->AddComponent<LumenAusf::Collider> ();

//        auto mr = go->AddComponent<LumenAusf::MeshRenderer> ();
//        mr->offsetX = td.atlasOffsetX;
//        mr->offsetY = td.atlasOffsetY;
//        mr->meshType = LumenAusf::TypeOfMesh::Dynamic;
//        mr->triangles = mr->trianglesOriginals = Engine->CreateQuadtc ();
//        mr->texture = AtlasTank;
//        mr->atlas = new LumenAusf::Atlas (mr);
//        mr->SetAtlas (LumenAusf::vec2 (td.atlasWAll, td.atlasHAll), LumenAusf::vec2 (td.atlasStart, td.atlasEnd));
//    }
//}

// struct EagleData
//{
//    LumenAusf::vec2 pos;
//    int atlasWAll;
//    int atlasHAll;
//    int atlasStart;
//    int atlasEnd;
//    float atlasOffsetX;
//    float atlasOffsetY;
//    float scale;
//};
// std::istream& operator>> (std::istream& is, EagleData& t)
//{
//    is >> t.pos;
//    is >> t.atlasWAll;
//    is >> t.atlasHAll;
//    is >> t.atlasStart;
//    is >> t.atlasEnd;
//    is >> t.atlasOffsetX;
//    is >> t.atlasOffsetY;
//    is >> t.scale;
//    return is;
//}

void Play::CreateEagle (ObjectConfig data, int number)
{
    auto go = new LumenAusf::GameObject ("Eagle");
    go->tag = "Block";
    go->transform->SetPosition (LumenAusf::vec2 (-1.f + data.scale + ((number % 8) * data.scale * 2), 0.5f - (number / 8) * data.scale * 2));
    go->transform->setLocalScale (LumenAusf::mat2x3::scale (data.scale));

    auto a = new LumenAusf::mat2x3 ();
    a->col0.x = 1;
    a->col0.y = 0.f;
    a->col1.x = 0.f;
    a->col1.y = static_cast<float> (windowWidth) / windowHeight;
    go->transform->setAspect (*a);

    go->AddComponent<LumenAusf::Collider> ();

    auto mr = go->AddComponent<LumenAusf::MeshRenderer> ();
    mr->offsetX = data.atlasOffsetX;
    mr->offsetY = data.atlasOffsetY;
    mr->meshType = LumenAusf::TypeOfMesh::Dynamic;
    mr->triangles = mr->trianglesOriginals = Engine->CreateQuadtc ();
    mr->texture = AtlasTank;
    mr->atlas = new LumenAusf::Atlas (mr);
    mr->SetAtlas (LumenAusf::vec2 (data.atlasWAll, data.atlasHAll), LumenAusf::vec2 (data.atlasStart, data.atlasEnd));

    auto df = go->AddComponent<GameOverController> ();
    df->SetAnchor (&running);

    //    mr->ResizeUV (LumenAusf::vec2 (1.f / (td.atlasWAll * 2.5f), 1.f / (td.atlasWAll * 2.5f)),
    //                  LumenAusf::vec2 (1.f / (td.atlasHAll * 2.5f), 1.f / (td.atlasHAll * 2.5f)));
}
