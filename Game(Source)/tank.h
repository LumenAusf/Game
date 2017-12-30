#pragma once

#ifndef TANK_H
#define TANK_H

#include "Source/collider.h"
#include "Source/gameobject.h"
#include "Source/meshrenderer.h"
#include "missile.h"
#include "src/audio.h"

class Tank
{
   public:
    static int num;
    LumenAusf::GameObject* go;
    Tank (LumenAusf::mat2x3 a)
    {
        go = new LumenAusf::GameObject (nullptr);
        go->transform->setAspect (a);
        go->name = "Tank " + std::to_string (num);
        num++;
    }
    void Start ();
    void Fire ();
    void Rotate (Arrows dir);
    void Move ();
    float getSpeed () const;
    void setSpeed (float value);
    int getMissileCount () const;
    void setMissileCount (int value);
    void setMissile (Missile* pref);
    void SetSounds (Audio* Start, Audio* Stay, Audio* Run, Audio* Fire);

    float Speed;
    int MissileCount;
    Missile* MissilePref;
    Arrows Direction;
    Audio* SoundStartEngine;
    Audio* SoundEngine;
    Audio* SoundRun;
    Audio* SoundFire;
};

#endif    // TANK_H
