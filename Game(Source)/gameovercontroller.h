#pragma once

#ifndef GAMEOVERCONTROLLER_H
#define GAMEOVERCONTROLLER_H

#include "Source/engine.h"

class GameOverController : public LumenAusf::Component
{
   public:
    GameOverController (LumenAusf::GameObject* owner) : LumenAusf::Component (owner) {}
    virtual ~GameOverController ();

    // Component interface
   public:
    void Awake ();
    void Start ();
    void Update ();
    void onEnable ();
    void onDisable ();
    void onDestroy ();
    void Destroy ();
    void SetAnchor (bool* a);
    bool* running;
};

#endif    // GAMEOVERCONTROLLER_H
