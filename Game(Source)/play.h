#pragma once

#ifndef PLAY_H
#define PLAY_H

#include <fstream>
#include <iostream>

#include "Source/engine.h"
#include "src/audio.h"
#include "tank.h"

class Play
{
   public:
    float speed = 0.045f;
    int windowHeight = 480;
    int windowWidth = 640;

    void Run ();
    void EventGetted (LumenAusf::EventItem item);

   private:
    bool running;
    LumenAusf::Engine* Engine;
    LumenAusf::Texture* textureGrass;
    LumenAusf::Texture* AtlasTank;
    Tank* goTank;
    Tank* goTank2;

    void DrawGrass ();
    bool LoadTextures ();
    Tank* InitTank (int AtlasStart, int AtlasEnd);
    void RenderGameObject (LumenAusf::GameObject* go /*, bool needNext = true*/);
    LumenAusf::GameObject* LoadGameObject (std::string TrianglesPath, LumenAusf::Texture* texture, int TrianglesCount);
    Tank* CreateTank (std::string TrianglesPath, LumenAusf::Texture* texture, int TrianglesCount, int AtlasStart, int AtlasEnd);
};

#endif    // PLAY_H
