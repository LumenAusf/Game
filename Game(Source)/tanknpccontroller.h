#pragma once

#ifndef TANKNPCCONTROLLER_H
#define TANKNPCCONTROLLER_H

#include <ctime>
#include "Source/engine.h"
#include "src/audio.h"

class TankNPCController : public LumenAusf::Component
{
   public:
    TankNPCController (LumenAusf::GameObject* owner) : LumenAusf::Component (owner) {}
    virtual ~TankNPCController ();

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
};

#endif    // TANKNPCCONTROLLER_H
