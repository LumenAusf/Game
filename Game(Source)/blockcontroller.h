#pragma once

#ifndef BLOCKCONTROLLER_H
#define BLOCKCONTROLLER_H

#include "play.h"

class BlockController : public LumenAusf::Component
{
   public:
    BlockController (LumenAusf::GameObject* owner) : LumenAusf::Component (owner) {}
    virtual ~BlockController ();

    int num;

    // Component interface
   public:
    void Awake ();
    void Start ();
    void Update ();
    void onEnable ();
    void onDisable ();
    void onDestroy ();
    void Destroy ();
};

#endif    // BLOCKCONTROLLER_H
