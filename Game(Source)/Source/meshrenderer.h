#pragma once

#ifndef MESHRENDERER_H
#define MESHRENDERER_H

#include <vector>
#include "gameobject.h"
#include "texture.h"
#include "triangle.h"
#include "vec2.h"

namespace LumenAusf
{
    class MeshRenderer;

    class Atlas
    {
       public:
        Atlas (MeshRenderer* mesh);
        Texture* texture;
        MeshRenderer* mesh;
        glm::vec2 elementCountXY, usefromTo;
        int startId, finishId;
        int sizeAtlasItem;
        int currentAtlasItem;
        void SetAtlas (Texture* texture, glm::vec2 elementCountXY, glm::vec2 UsefromTo);
        void Next ();
    };

    enum TypeOfMesh
    {
        Static,     // Texture
        Dynamic,    // Atlas
    };

    class MeshRenderer : public Component
    {
       public:
        TypeOfMesh meshType = TypeOfMesh::Static;
        Atlas* atlas = nullptr;
        virtual ~MeshRenderer ();
        Texture* texture = nullptr;
        std::vector<trianglePTC> triangles;
        std::vector<trianglePTC> trianglesOriginals;
        float offsetX = 0.f;
        float offsetY = 0.f;

        MeshRenderer (GameObject* owner) : Component (owner) {}
        //        MeshRenderer (TypeOfMesh typeMesh, std::vector<tri2> triangles, Texture* texture);
        //        MeshRenderer (TypeOfMesh typeMesh, std::vector<tri2> triangles, Texture* texture, float offsetx, float offsety);
        void SetAtlas (glm::vec2 elementCountXY, glm::vec2 UsefromTo);
        void ResizeUV (glm::vec2 LeftRight, glm::vec2 UpDown);
        void Awake ();
        void Start ();
        void Update ();
        void onEnable ();
        void onDisable ();

        // Component interface
       public:
        void Destroy ();
    };
}

#endif    // MESHRENDERER_H
