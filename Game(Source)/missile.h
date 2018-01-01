#pragma once

#ifndef MISSILE_H
#define MISSILE_H

#include "play.h"
//#include "Source/gameobject.h"
#include "src/audio.h"

class Tank;

class Missile
{
   public:
    Missile (Tank* owner) { tank = owner; }
    void Start ();
    void Boom ();

    float speed = 0.5f;
    Audio* SoundFly;
    Audio* SoundBoom;
    Tank* tank;
};

#endif    // MISSILE_H
