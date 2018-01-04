#pragma once

#ifndef MISSILE_H
#define MISSILE_H

#include "missilecontroller.h"
#include "play.h"
#include "src/audio.h"

class MissileController;

struct MissileData
{
    int trianglesCount;
    std::vector<LumenAusf::tri2> triangles;
    int atlasWAll;
    int atlasHAll;
    int atlasStart;
    int atlasEnd;
    float atlasOffsetX;
    float atlasOffsetY;
    float scale;
    std::string pathSoundRun;
    std::string pathSoundFire;
};

std::istream& operator>> (std::istream& is, MissileData& t);

class Missile
{
   public:
    Missile (LumenAusf::GameObject* owner, std::string configPath, LumenAusf::Texture* texture, bool isUser);
    void SetAspect (LumenAusf::mat2x3 aspect);
    void SetAspect (float width, float height);

    float speed = .5f;
    LumenAusf::GameObject* tank;
    LumenAusf::GameObject* go;
    LumenAusf::MeshRenderer* mr;
    LumenAusf::Collider* collider;
    MissileController* mc;
};

#endif    // MISSILE_H
