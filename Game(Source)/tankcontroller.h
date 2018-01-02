#pragma once

#ifndef TANKCONTROLLER_H
#define TANKCONTROLLER_H

//#include "Source/gameobject.h"
#include "Source/engine.h"
#include "missile.h"
#include "src/audio.h"

class TankController : public LumenAusf::Component
{
   public:
    TankController (LumenAusf::GameObject* owner) : LumenAusf::Component (owner) {}
    virtual ~TankController ();

    // Component interface
   public:
    void Awake ();
    void Start ();
    void Update ();
    void onEnable ();
    void onDisable ();
    void onDestroy ();

    void Fire ();
    void Rotate (Arrows dir);
    void Move ();
    void SetSounds (Audio* Start, Audio* Stay, Audio* Run, Audio* Fire);
    void SetTextureMissile (LumenAusf::Texture* tex);

    float Speed = 0.000045f;
    int MissileCount;
    Arrows Direction = Arrows::Up;
    Audio* SoundStartEngine;
    Audio* SoundEngine;
    Audio* SoundRun;
    Audio* SoundFire;
    LumenAusf::Texture* textureForMissile = nullptr;

    bool previousSpace = false;

    // Component interface
   public:
    void Destroy ();
};

#endif    // TANKCONTROLLER_H
