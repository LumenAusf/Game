#pragma once

#ifndef TANK_H
#define TANK_H

#include "play.h"
#include "tankcontroller.h"
#include "tanknpccontroller.h"

class Missile;
class TankController;
class TankNPCController;

struct TankData
{
    LumenAusf::vec2 pos;
    int atlasWAll;
    int atlasHAll;
    int atlasStart;
    int atlasEnd;
    float atlasOffsetX;
    float atlasOffsetY;
    float scale;
    std::string pathSoundStart;
    std::string pathSoundStay;
    std::string pathSoundRun;
    std::string pathSoundFire;
};

std::istream& operator>> (std::istream& is, TankData& t);

class Tank
{
   public:
    Tank (std::string configPath, LumenAusf::Texture* texture, bool isUser, bool* running);
    void SetAspect (LumenAusf::mat2x3 aspect);
    void SetAspect (float width, float height);

    static int num;
    LumenAusf::GameObject* go;
    LumenAusf::MeshRenderer* mr;
    LumenAusf::Collider* collider;
    TankController* tc;
    TankNPCController* tnc;

   private:
    void CreateUserTank (std::string configPath, LumenAusf::Texture* texture, bool* running);
    void CreateNPCTank (std::string configPath, LumenAusf::Texture* texture);
};

#endif    // TANK_H
