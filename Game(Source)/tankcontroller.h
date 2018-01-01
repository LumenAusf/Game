#pragma once

#ifndef TANKCONTROLLER_H
#define TANKCONTROLLER_H

//#include "Source/gameobject.h"
#include "Source/engine.h"
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

    float Speed = 0.000045f;
    int MissileCount;
    Arrows Direction;
    Audio* SoundStartEngine;
    Audio* SoundEngine;
    Audio* SoundRun;
    Audio* SoundFire;

    bool previousSpace = false;
};

#endif    // TANKCONTROLLER_H
