#pragma once

#ifndef MAP_H
#define MAP_H

#include "play.h"

class BlockController;

class Map
{
   public:
    static Map* Instance ();
    LumenAusf::vec2 NearestPoint (LumenAusf::vec2 currPos);

    BlockController* field[9][9];

   private:
    Map ();

    static Map* map;
};

#endif    // MAP_H
