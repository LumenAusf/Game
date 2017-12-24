#pragma once

#ifndef MISSILE_H
#define MISSILE_H

#include "Source/gameobject.h"
#include "src/audio.h"

class Missile : public LumenAusf::GameObject
{
   public:
    Missile ();
    void Start ();
    void Boom ();

    float speed;
    Audio* SoundFly;
    Audio* SoundBoom;
};

#endif    // MISSILE_H
