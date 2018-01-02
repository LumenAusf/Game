#include "meshrenderer.h"

namespace LumenAusf
{
    MeshRenderer::~MeshRenderer () {}

    void MeshRenderer::SetAtlas (vec2 elementCountXY, vec2 UsefromTo)
    {
        if (atlas == nullptr)
            return;
        atlas->SetAtlas (texture, elementCountXY, UsefromTo);
    }

    void MeshRenderer::ResizeUV (vec2 LeftRight, vec2 UpDown)
    {
        std::cerr << "RERERE" << std::endl;
        for (size_t a = 0; a < triangles.size (); a++)
        {
            for (auto i = 0; i < 3; i++)
            {
                std::cerr << "Before X:" << triangles[a].v[i].uv.x << " Y:" << triangles[a].v[i].uv.y << std::endl;
                std::cerr << "Originals X:" << trianglesOriginals[a].v[i].uv.x << " Y:" << trianglesOriginals[a].v[i].uv.y << std::endl;

                if (trianglesOriginals[a].v[i].uv.x > 0.5f)
                    triangles[a].v[i].uv.x -= LeftRight.y;
                else if (trianglesOriginals[a].v[i].uv.x < 0.5f)
                    triangles[a].v[i].uv.x += LeftRight.x;

                if (trianglesOriginals[a].v[i].uv.y > 0.5f)
                    triangles[a].v[i].uv.y -= UpDown.x;
                else if (trianglesOriginals[a].v[i].uv.y < 0.5f)
                    triangles[a].v[i].uv.y += UpDown.y;

                std::cerr << "After X:" << triangles[a].v[i].uv.x << " Y:" << triangles[a].v[i].uv.y << std::endl;
            }
        }
    }

    void MeshRenderer::Awake () {}

    void MeshRenderer::Start () {}

    void MeshRenderer::Update () { /*std::cout << "Updated MeshRenderer" << std::endl;*/}

    void MeshRenderer::onEnable () {}

    void MeshRenderer::onDisable () {}

    void MeshRenderer::Destroy () { this->~MeshRenderer (); }
}
