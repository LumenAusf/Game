#include "missile.h"

Missile::Missile (LumenAusf::GameObject* owner, std::string configPath, LumenAusf::Texture* texture, bool isUser)
{
    tank = owner;
    go = new LumenAusf::GameObject (nullptr);
    go->name = tank->name + " Missile";
    go->tag = owner->GetComponent<TankController> ()->Mode == 0 ? "Missile" : "MissileNPC";

    std::ifstream fd (configPath);
    if (!fd.is_open ())
    {
        go->~GameObject ();
        std::cerr << "Can`t open config file: " + configPath << std::endl;
        return;
    }

    auto td = MissileData ();
    fd >> td;
    fd.close ();
    go->transform->setLocalPosition (tank->transform->getGlobalPosition ());
    go->transform->setLocalScale (LumenAusf::mat2x3::scale (td.scale));
    go->transform->setAspect (owner->transform->getAspect ());

    collider = go->AddComponent<LumenAusf::Collider> ();

    mr = go->AddComponent<LumenAusf::MeshRenderer> ();
    mr->offsetX = td.atlasOffsetX;
    mr->offsetY = td.atlasOffsetY;
    mr->meshType = LumenAusf::TypeOfMesh::Dynamic;
    mr->triangles = mr->trianglesOriginals = Play::getEngine ()->CreateQuadtc ();
    mr->texture = texture;
    mr->atlas = new LumenAusf::Atlas (mr);

    mr->SetAtlas (LumenAusf::vec2 (td.atlasWAll, td.atlasHAll), LumenAusf::vec2 (td.atlasStart, td.atlasEnd));
    mr->ResizeUV (LumenAusf::vec2 (1.f / (td.atlasWAll * 2.5f), 1.f / (td.atlasWAll * 2.5f)),
                  LumenAusf::vec2 (1.f / (td.atlasHAll * 2.5f), 1.f / (td.atlasHAll * 2.5f)));

    mc = go->AddComponent<MissileController> ();
    auto d = createAudio (td.pathSoundRun.c_str (), 0, SDL_MIX_MAXVOLUME / 4);
    auto e = createAudio (td.pathSoundFire.c_str (), 0, SDL_MIX_MAXVOLUME);
    mc->SetSounds (d, e);
    mc->Direction = isUser ? tank->GetComponent<TankController> ()->Direction : tank->GetComponent<TankNPCController> ()->Direction;
    switch (mc->Direction)
    {
        case Arrows::Up:
            go->transform->setLocalPosition (go->transform->getLocalPosition () *
                                             LumenAusf::mat2x3::move (LumenAusf::vec2 (0.f, tank->transform->getLocalScale ().col0.x)));
            break;
        case Arrows::Down:
            go->transform->setLocalPosition (go->transform->getLocalPosition () *
                                             LumenAusf::mat2x3::move (LumenAusf::vec2 (0.f, -tank->transform->getLocalScale ().col0.x)));
            break;
        case Arrows::Right:
            go->transform->setLocalPosition (go->transform->getLocalPosition () *
                                             LumenAusf::mat2x3::move (LumenAusf::vec2 (tank->transform->getLocalScale ().col0.x, 0.f)));
            break;
        case Arrows::Left:
            go->transform->setLocalPosition (go->transform->getLocalPosition () *
                                             LumenAusf::mat2x3::move (LumenAusf::vec2 (-tank->transform->getLocalScale ().col0.x, 0.f)));
            break;
    }
    mc->Speed = speed;
}

std::istream& operator>> (std::istream& is, MissileData& t)
{
    is >> t.atlasWAll;
    is >> t.atlasHAll;
    is >> t.atlasStart;
    is >> t.atlasEnd;
    is >> t.atlasOffsetX;
    is >> t.atlasOffsetY;
    is >> t.scale;
    is >> t.pathSoundRun;
    is >> t.pathSoundFire;
    return is;
}
