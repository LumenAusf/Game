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

    void MeshRenderer::Awake () {}

    void MeshRenderer::Start () {}

    void MeshRenderer::Update () { /*std::cout << "Updated MeshRenderer" << std::endl;*/}

    void MeshRenderer::onEnable () {}

    void MeshRenderer::onDisable () {}
}
