#pragma once

#ifndef ATLAS_H
#define ATLAS_H

#include "meshrenderer.h"
#include "texture.h"
#include "vec2.h"

namespace LumenAusf
{
    class Atlas
    {
       public:
        Atlas (MeshRenderer* mesh);
        Texture* texture;
        MeshRenderer* mesh;
        vec2 elementCountXY, usefromTo;
        int startId, finishId;
        int sizeAtlasItem;
        int currentAtlasItem;
        void SetAtlas (Texture* texture, vec2 elementCountXY, vec2 UsefromTo);
        void Next ();
    };
}

#endif    // ATLAS_H
