#pragma once

#ifndef PLAY_H
#define PLAY_H

#include <fstream>
#include <iostream>

#include <glm/gtc/matrix_transform.hpp>
#include "Source/collider.h"
#include "Source/engine.h"
#include "gameovercontroller.h"
#include "missile.h"
#include "src/audio.h"
#include "tank.h"

class Tank;

struct ObjectConfig
{
    int atlasWAll;
    int atlasHAll;
    int atlasStart;
    int atlasEnd;
    float atlasOffsetX;
    float atlasOffsetY;
    float scale;
};
std::istream& operator>> (std::istream& is, ObjectConfig& t);

class Play
{
   public:
    float speed = 0.00045f;
    int windowHeight = 540;
    int windowWidth = 960;

    void Run ();
    void EventGetted (LumenAusf::EventItem item);

    static LumenAusf::Engine* getEngine ();

   private:
    bool running;
    static LumenAusf::Engine* Engine;
    LumenAusf::Texture* textureGrass;
    LumenAusf::Texture* AtlasTank;
    //    Tank* goTank;
    //    Tank* goTank2;
    //    Tank* goTank3;
    //    Tank* goTank4;
    //    Tank* goTank5;
    LumenAusf::GameObject* got;

    void DrawGrass ();
    bool LoadTextures ();
    //    Tank* InitTank (int AtlasStart, int AtlasEnd, float offsetX = 0.f, float offsetY = 0.f);
    void RenderGameObject (LumenAusf::GameObject* go /*, bool needNext = true*/);
    void RenderAll ();
    void InitScene (std::string configMap, std::string configBlocks, std::string configTank, std::string configNpcTank, std::string configEagle,
                    std::string configMissile);
    //    void CreateBlocks (std::string configBlocks, std::string configMap);
    //    void CreateEagle (std::string configEagle);
    LumenAusf::GameObject* LoadGameObject (std::string TrianglesPath, LumenAusf::Texture* texture, int TrianglesCount);
    void CreateBlock (ObjectConfig data, int number);
    void CreateEagle (ObjectConfig data, int number);
    void CreateTank (ObjectConfig data, int number, std::vector<std::string> audioTank, std::vector<std::string> audioMissile, bool isUser);
    //    Tank*
    //    CreateTank (std::string TrianglesPath, LumenAusf::Texture* texture, int TrianglesCount, int AtlasStart, int AtlasEnd, float offsetX, float
    //    offsetY);
};

#endif    // PLAY_H
