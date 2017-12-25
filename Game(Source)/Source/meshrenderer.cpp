#include "meshrenderer.h"

namespace LumenAusf
{
    MeshRenderer::~MeshRenderer()
    {

    }

    MeshRenderer::MeshRenderer (TypeOfMesh typeMesh, std::vector<tri2> triangles, Texture* texture)
    {
        meshType = typeMesh;
        this->triangles = triangles;
        this->trianglesOriginals = triangles;
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

    MeshRenderer::MeshRenderer(TypeOfMesh typeMesh, std::vector<tri2> triangles, Texture*texture, float offsetx, float offsety)
    {
        meshType = typeMesh;
        this->triangles = triangles;
        this->trianglesOriginals = triangles;
        this->texture = texture;
        this->offsetX = offsetx;
        this->offsetY = offsety;

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

    void MeshRenderer::Awake () {}

    void MeshRenderer::Start () {}

    void MeshRenderer::Update () {}

    void MeshRenderer::onEnable () {}

    void MeshRenderer::onDisable () {}

    bool MeshRenderer::getEnabled () const { return enabled; }

    void MeshRenderer::setEnabled (bool value) { enabled = value; }

    GameObject* MeshRenderer::getGameObject () const { return gameObject; }

    void MeshRenderer::setGameObject (GameObject* value) { gameObject = value; }
}
