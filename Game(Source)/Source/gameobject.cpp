#include "gameobject.h"

void LumenAusf::GameObject::SetAtlas (LumenAusf::Texture* texture, LumenAusf::vec2 elementCountXY, LumenAusf::vec2 UsefromTo)
{
    isAtlas = true;
    this->texture = texture;
    this->elementCountXY = elementCountXY;
    this->usefromTo = UsefromTo;
    currentAtlasItem = 0;

    for (unsigned long i = 0; i < triangles.size (); i++)
    {
        for (int j = 0; j < 3; j++)
        {
            triangles.at (i).v[j].uv.x *= 1 / this->elementCountXY.x;
            triangles.at (i).v[j].uv.x += (1 / this->elementCountXY.x) * ((int)this->usefromTo.x % (int)this->elementCountXY.x);
            triangles.at (i).v[j].uv.y *= 1 / this->elementCountXY.y;
            triangles.at (i).v[j].uv.y += (this->elementCountXY.y - 1) / this->elementCountXY.y;
        }
    }
}

void LumenAusf::GameObject::SetTexture (LumenAusf::Texture* texture) { this->texture = texture; }

void LumenAusf::GameObject::Next ()
{
    if (!isAtlas)
        return;

    if (currentAtlasItem >= (int)this->usefromTo.y)
        currentAtlasItem = 0;

    if (currentAtlasItem == 0)
    {
        for (unsigned long i = 0; i < triangles.size (); i++)
        {
            for (int j = 0; j < 3; j++)
            {
                triangles.at (i).v[j].uv.x = trianglesOriginals.at (i).v[j].uv.x * 1 / this->elementCountXY.x;
                triangles.at (i).v[j].uv.x += (1 / this->elementCountXY.x) * ((int)this->usefromTo.x % (int)this->elementCountXY.x);
                triangles.at (i).v[j].uv.y = trianglesOriginals.at (i).v[j].uv.y * 1 / this->elementCountXY.y;
                triangles.at (i).v[j].uv.y += (this->elementCountXY.y - 1) / this->elementCountXY.y;
            }
        }
    }
    else if ((currentAtlasItem + (int)this->usefromTo.x) % (int)elementCountXY.x == 0)
    {
        for (unsigned long i = 0; i < triangles.size (); i++)
        {
            for (int j = 0; j < 3; j++)
            {
                triangles.at (i).v[j].uv.x -= (1 / this->elementCountXY.x) * ((int)this->elementCountXY.x - 1);
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
