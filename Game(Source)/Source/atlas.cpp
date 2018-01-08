#include "meshrenderer.h"

namespace LumenAusf
{
    Atlas::Atlas (MeshRenderer* mesh) { this->mesh = mesh; }

    void Atlas::SetAtlas (LumenAusf::Texture* texture, glm::vec2 elementCountXY, glm::vec2 UsefromTo)
    {
        this->texture = texture;
        this->elementCountXY = elementCountXY;
        this->usefromTo = UsefromTo;
        currentAtlasItem = 0;

        for (unsigned long i = 0; i < mesh->triangles.size (); i++)
        {
            for (int j = 0; j < 3; j++)
            {
                mesh->triangles.at (i).v[j].uv.x = mesh->trianglesOriginals.at (i).v[j].uv.x * 1 / this->elementCountXY.x;
                mesh->triangles.at (i).v[j].uv.x +=
                    (1 / this->elementCountXY.x) * (static_cast<int> (this->usefromTo.x) % static_cast<int> (this->elementCountXY.x));
                if (mesh->offsetX > 0.001f)
                    mesh->triangles.at (i).v[j].uv.x += mesh->offsetX / texture->get_width ();

                mesh->triangles.at (i).v[j].uv.y = mesh->trianglesOriginals.at (i).v[j].uv.y * 1 / this->elementCountXY.y;
                mesh->triangles.at (i).v[j].uv.y +=
                    (this->elementCountXY.y - 1 - (static_cast<int> (this->usefromTo.x) / static_cast<int> (this->elementCountXY.x))) /
                    this->elementCountXY.y;
                if (mesh->offsetY > 0.001f)
                    mesh->triangles.at (i).v[j].uv.y += mesh->offsetY / texture->get_height ();
            }
        }
    }

    void Atlas::Next ()
    {
        //    if (!isAtlas)
        //        return;

        //    float offsetX = 1.5f;
        //    float offsetY = 0;

        if (currentAtlasItem + static_cast<int> (this->usefromTo.x) >= static_cast<int> (this->usefromTo.y))
            currentAtlasItem = 0;

        if (currentAtlasItem == 0)
        {
            for (unsigned long i = 0; i < mesh->triangles.size (); i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    mesh->triangles.at (i).v[j].uv.x = mesh->trianglesOriginals.at (i).v[j].uv.x * 1 / this->elementCountXY.x;
                    mesh->triangles.at (i).v[j].uv.x +=
                        (1 / this->elementCountXY.x) * (static_cast<int> (this->usefromTo.x) % static_cast<int> (this->elementCountXY.x));
                    if (mesh->offsetX > 0.001f)
                        mesh->triangles.at (i).v[j].uv.x += mesh->offsetX / static_cast<float> (texture->get_width ());

                    mesh->triangles.at (i).v[j].uv.y = mesh->trianglesOriginals.at (i).v[j].uv.y * 1 / this->elementCountXY.y;
                    mesh->triangles.at (i).v[j].uv.y +=
                        (this->elementCountXY.y - 1 - (static_cast<int> (this->usefromTo.x) / static_cast<int> (this->elementCountXY.x))) /
                        this->elementCountXY.y;
                    if (mesh->offsetY > 0.001f)
                        mesh->triangles.at (i).v[j].uv.y += mesh->offsetY / static_cast<float> (texture->get_height ());
                }
            }
        }
        else if ((currentAtlasItem + static_cast<int> (this->usefromTo.x)) % static_cast<int> (elementCountXY.x) == 0)
        {
            for (unsigned long i = 0; i < mesh->triangles.size (); i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    mesh->triangles.at (i).v[j].uv.x -= (1 / this->elementCountXY.x) * (static_cast<int> (this->elementCountXY.x) - 1);
                    mesh->triangles.at (i).v[j].uv.y -= (1 / this->elementCountXY.y);
                }
            }
        }
        else
        {
            for (unsigned long i = 0; i < mesh->triangles.size (); i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    mesh->triangles.at (i).v[j].uv.x += (1 / this->elementCountXY.x);
                }
            }
        }
        ++currentAtlasItem;
    }
}
