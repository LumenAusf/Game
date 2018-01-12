#include "map.h"
#include <cmath>

Map* Map::map = nullptr;

Map* Map::Instance ()
{
    if (map == nullptr)
        map = new Map ();
    return map;
}

LumenAusf::vec2 Map::NearestPoint (LumenAusf::vec2 currPos)
{
    auto objX = currPos.x;
    auto objY = currPos.y;

    float sumOld = 10;

    int nearestI = INT32_MAX, nearestJ = INT32_MAX;
    for (auto i = 0; i < 9; i++)
        for (auto j = 0; j < 9; j++)
        {
            auto mapX = -1.f + 0.0625f + (i * 0.0625f * 2);
            auto mapY = 0.5f - j * 0.0625f * 2;

            auto lengthX = std::abs (objX - mapX);
            auto lengthY = std::abs (objY - mapY);

            if (lengthX + lengthY <= sumOld)
            {
                nearestI = i;
                nearestJ = j;
                sumOld = lengthX + lengthY;
            }
        }

    return LumenAusf::vec2 (-1.f + 0.0625f + (nearestI * 0.0625f * 2), 0.5f - nearestJ * 0.0625f * 2);
}

Map::Map ()
{
    for (auto a : field) a = nullptr;
}
