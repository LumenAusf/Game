#pragma once

#ifndef MESHRENDERER_H
#define MESHRENDERER_H

#include <vector>
#include "atlas.h"
#include "lacomponent.h"
#include "texture.h"
#include "triangle.h"

namespace LumenAusf
{
    class Atlas;

    enum TypeOfMesh
    {
        Static,     // Texture
        Dynamic,    // Atlas
    };

    class MeshRenderer : LAComponent
    {
       public:
        TypeOfMesh meshType = TypeOfMesh::Static;
        Atlas* atlas = nullptr;

        Texture* texture = nullptr;
        std::vector<tri2> triangles;
        std::vector<tri2> trianglesOriginals;
        float offsetX = 0.f;
        float offsetY = 0.f;

        //        MeshRenderer(TypeOfMesh typeMesh, std::vector<tri2> triangles);
        MeshRenderer (TypeOfMesh typeMesh, std::vector<tri2> triangles, Texture* texture);
        void SetAtlas (vec2 elementCountXY, vec2 UsefromTo);
        // LAComponent interface
        //        void Awake () override;
        //        void Start () override;
        //        void Update () override;
        //        void onEnable () override;
        //        void onDisable () override;
    };
}

#endif    // MESHRENDERER_H
