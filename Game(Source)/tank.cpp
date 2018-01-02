#include "tank.h"

int Tank::num = 0;

Tank::Tank (std::string configPath, LumenAusf::Texture* texture, bool isUser)
{
    if (isUser)
        CreateUserTank (configPath, texture);
    else
        CreateNPCTank (configPath, texture);
}

void Tank::SetAspect (LumenAusf::mat2x3 aspect) { go->transform->setAspect (aspect); }

void Tank::SetAspect (float width, float height)
{
    auto a = new LumenAusf::mat2x3 ();
    a->col0.x = 1;
    a->col0.y = 0.f;
    a->col1.x = 0.f;
    a->col1.y = static_cast<float> (width) / height;

    go->transform->setAspect (*a);
}

void Tank::CreateUserTank (std::string configPath, LumenAusf::Texture* texture)
{
    go = new LumenAusf::GameObject (nullptr);
    go->name = "UserTank";
    go->tag = "TankUser";

    std::ifstream fd (configPath);
    if (!fd.is_open ())
    {
        go->~GameObject ();
        std::cerr << "Can`t open : " + configPath << std::endl;
        return;
    }
    auto td = TankData ();
    fd >> td;

    go->transform->SetPosition (td.pos);
    go->transform->setLocalScale (LumenAusf::mat2x3::scale (td.scale));

    collider = go->AddComponent<LumenAusf::Collider> ();

    mr = go->AddComponent<LumenAusf::MeshRenderer> ();
    mr->offsetX = td.atlasOffsetX;
    mr->offsetY = td.atlasOffsetY;
    mr->meshType = LumenAusf::TypeOfMesh::Dynamic;
    mr->triangles = mr->trianglesOriginals = td.triangles;
    mr->texture = texture;
    mr->atlas = new LumenAusf::Atlas (mr);

    mr->SetAtlas (LumenAusf::vec2 (td.atlasWAll, td.atlasHAll), LumenAusf::vec2 (td.atlasStart, td.atlasEnd));

    tc = go->AddComponent<TankController> ();
    auto b = createAudio (td.pathSoundStart.c_str (), 0, SDL_MIX_MAXVOLUME / 2);
    auto c = createAudio (td.pathSoundStay.c_str (), 1, SDL_MIX_MAXVOLUME / 2);
    auto d = createAudio (td.pathSoundRun.c_str (), 0, SDL_MIX_MAXVOLUME / 2);
    auto e = createAudio (td.pathSoundFire.c_str (), 0, SDL_MIX_MAXVOLUME);
    tc->SetSounds (b, c, d, e);
    tc->SetTextureMissile (texture);
}

void Tank::CreateNPCTank (std::string configPath, LumenAusf::Texture* texture)
{
    go = new LumenAusf::GameObject (nullptr);
    go->name = "NPCTank " + std::to_string (num);
    go->tag = "TankNPC";
    num++;

    std::ifstream fd (configPath);
    if (!fd.is_open ())
    {
        go->~GameObject ();
        std::cerr << "Can`t open : " + configPath << std::endl;
        return;
    }
    auto td = TankData ();
    fd >> td;

    go->transform->SetPosition (td.pos);
    go->transform->setLocalScale (LumenAusf::mat2x3::scale (td.scale));

    collider = go->AddComponent<LumenAusf::Collider> ();

    mr = go->AddComponent<LumenAusf::MeshRenderer> ();
    mr->offsetX = td.atlasOffsetX;
    mr->offsetY = td.atlasOffsetY;
    mr->meshType = LumenAusf::TypeOfMesh::Dynamic;
    mr->triangles = mr->trianglesOriginals = td.triangles;
    mr->texture = texture;
    mr->atlas = new LumenAusf::Atlas (mr);

    mr->SetAtlas (LumenAusf::vec2 (td.atlasWAll, td.atlasHAll), LumenAusf::vec2 (td.atlasStart, td.atlasEnd));

    tnc = go->AddComponent<TankNPCController> ();
    auto b = createAudio (td.pathSoundStart.c_str (), 0, SDL_MIX_MAXVOLUME / 2);
    auto c = createAudio (td.pathSoundStay.c_str (), 1, SDL_MIX_MAXVOLUME / 2);
    auto d = createAudio (td.pathSoundRun.c_str (), 0, SDL_MIX_MAXVOLUME / 2);
    auto e = createAudio (td.pathSoundFire.c_str (), 0, SDL_MIX_MAXVOLUME);
    tnc->SetSounds (b, c, d, e);
}

std::istream& operator>> (std::istream& is, TankData& t)
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
    is >> t.pathSoundStart;
    is >> t.pathSoundStay;
    is >> t.pathSoundRun;
    is >> t.pathSoundFire;
    return is;
}
