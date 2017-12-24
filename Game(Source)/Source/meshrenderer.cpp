#include "meshrenderer.h"

namespace LumenAusf
{
    MeshRenderer::MeshRenderer (TypeOfMesh typeMesh, std::vector<tri2> triangles, Texture* texture)
    {
        meshType = typeMesh;
        this->triangles = triangles;
        this->texture = texture;

        switch (typeMesh)
        {
            case TypeOfMesh::Dynamic:
                atlas = new Atlas (this);
                break;
            case TypeOfMesh::Static:

                break;
        }
    }

    void MeshRenderer::SetAtlas (vec2 elementCountXY, vec2 UsefromTo)
    {
        if (atlas == nullptr)
            return;
        atlas->SetAtlas (texture, elementCountXY, UsefromTo);
    }
}
