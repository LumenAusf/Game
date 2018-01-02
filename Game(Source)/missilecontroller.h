#pragma once

#ifndef MISSILECONTROLLER_H
#define MISSILECONTROLLER_H

#include "src/audio.h"
#include "tank.h"

class Tank;

class MissileController : public LumenAusf::Component
{
   public:
    MissileController (LumenAusf::GameObject* owner) : LumenAusf::Component (owner) {}
    virtual ~MissileController ();

    // Component interface
   public:
    void Awake ();
    void Start ();
    void Update ();
    void onEnable ();
    void onDisable ();
    void onDestroy ();
    void SetSounds (Audio* r, Audio* f);

    Arrows Direction;
    Audio* SoundRun;
    Audio* SoundFire;
    Tank* TOwner;
    float Speed;

    // Component interface
   public:
    void Destroy ();
};

#endif    // MISSILECONTROLLER_H
