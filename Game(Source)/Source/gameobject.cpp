#include "gameobject.h"

void LumenAusf::GameObject::SetAtlas (LumenAusf::Texture* texture, LumenAusf::vec2 elementCountXY, LumenAusf::vec2 UsefromTo)
{
    float offsetX = 1.5f;
    float offsetY = 0;

    isAtlas = true;
    this->texture = texture;
    this->elementCountXY = elementCountXY;
    this->usefromTo = UsefromTo;
    currentAtlasItem = 0;

    for (unsigned long i = 0; i < triangles.size (); i++)
    {
        for (int j = 0; j < 3; j++)
        {
            triangles.at (i).v[j].uv.x = trianglesOriginals.at (i).v[j].uv.x * 1 / this->elementCountXY.x;
            triangles.at (i).v[j].uv.x +=
                (1 / this->elementCountXY.x) * (static_cast<int> (this->usefromTo.x) % static_cast<int> (this->elementCountXY.x));
            if (offsetX > 0.001f)
                triangles.at (i).v[j].uv.x += offsetX / texture->get_width ();

            triangles.at (i).v[j].uv.y = trianglesOriginals.at (i).v[j].uv.y * 1 / this->elementCountXY.y;
            triangles.at (i).v[j].uv.y +=
                (this->elementCountXY.y - 1 - (static_cast<int> (this->usefromTo.x) / static_cast<int> (this->elementCountXY.x))) /
                this->elementCountXY.y;
            if (offsetY > 0.001f)
                triangles.at (i).v[j].uv.y += offsetY / texture->get_height ();
        }
    }
}

void LumenAusf::GameObject::SetTexture (LumenAusf::Texture* texture) { this->texture = texture; }

void LumenAusf::GameObject::Next ()
{
    if (!isAtlas)
        return;

    float offsetX = 1.5f;
    float offsetY = 0;

    if (currentAtlasItem + static_cast<int> (this->usefromTo.x) >= static_cast<int> (this->usefromTo.y))
        currentAtlasItem = 0;

    if (currentAtlasItem == 0)
    {
        for (unsigned long i = 0; i < triangles.size (); i++)
        {
            for (int j = 0; j < 3; j++)
            {
                triangles.at (i).v[j].uv.x = trianglesOriginals.at (i).v[j].uv.x * 1 / this->elementCountXY.x;
                triangles.at (i).v[j].uv.x +=
                    (1 / this->elementCountXY.x) * (static_cast<int> (this->usefromTo.x) % static_cast<int> (this->elementCountXY.x));
                if (offsetX > 0.001f)
                    triangles.at (i).v[j].uv.x += offsetX / static_cast<float> (texture->get_width ());

                triangles.at (i).v[j].uv.y = trianglesOriginals.at (i).v[j].uv.y * 1 / this->elementCountXY.y;
                triangles.at (i).v[j].uv.y +=
                    (this->elementCountXY.y - 1 - (static_cast<int> (this->usefromTo.x) / static_cast<int> (this->elementCountXY.x))) /
                    this->elementCountXY.y;
                if (offsetY > 0.001f)
                    triangles.at (i).v[j].uv.y += offsetY / static_cast<float> (texture->get_height ());
            }
        }
    }
    else if ((currentAtlasItem + static_cast<int> (this->usefromTo.x)) % static_cast<int> (elementCountXY.x) == 0)
    {
        for (unsigned long i = 0; i < triangles.size (); i++)
        {
            for (int j = 0; j < 3; j++)
            {
                triangles.at (i).v[j].uv.x -= (1 / this->elementCountXY.x) * (static_cast<int> (this->elementCountXY.x) - 1);
                triangles.at (i).v[j].uv.y -= (1 / this->elementCountXY.y);
            }
        }
    }
    else
    {
        for (unsigned long i = 0; i < triangles.size (); i++)
        {
            for (int j = 0; j < 3; j++)
            {
                triangles.at (i).v[j].uv.x += (1 / this->elementCountXY.x);
            }
        }
    }
    ++currentAtlasItem;
}

void LumenAusf::GameObject::SetPosition (LumenAusf::vec2 position) { transform.position = mat2x3::identity () * mat2x3::move (position); }
