#include "collider.h"

namespace LumenAusf
{
    static bool IsIntersect (v2* array_1, mat2x3 first, v2* array_2, mat2x3 second)
    {
#define vectP_z(v, a, b) (((v).x - (a).x) * ((v).y - (b).y) - ((v).y - (a).y) * ((v).x - (b).x))
        int i, j, next_i, next_j;
        for (int i = 0; i < 3; i++)
        {
            next_i = i == 3 - 1 ? 0 : i + 1;
            for (j = 0; j < 3; j++)
            {
                next_j = j == 3 - 1 ? 0 : j + 1;
                if (vectP_z (array_1[next_i].pos * first, array_1[i].pos * first, array_2[j].pos * second) *
                            vectP_z (array_1[next_i].pos * first, array_1[i].pos * first, array_2[next_j].pos * second) <
                        0 &&
                    vectP_z (array_2[next_j].pos * second, array_2[j].pos * second, array_1[i].pos * first) *
                            vectP_z (array_2[next_j].pos * second, array_2[j].pos * second, array_1[next_i].pos * first) <
                        0)
                    return true;
            }
        }
        bool a = vectP_z (array_2[0].pos * second, array_2[3 - 1].pos * second, array_1[0].pos * first) < 0;
        for (j = 1; j < 3; j++)
            if (a != vectP_z (array_2[j].pos * second, array_2[j - 1].pos * second, array_1[0].pos * first) < 0)
                break;
        if (j == 3)
            return true;

        a = vectP_z (array_1[0].pos * first, array_1[3 - 1].pos * first, array_2[0].pos * second) < 0;
        for (i = 1; i < 3; i++)
            if (a != vectP_z (array_1[i].pos * first, array_1[i - 1].pos * first, array_2[0].pos * second) < 0)
                break;
        return i == 3;
    }

    Collider::Collider (GameObject* owner) : Component (owner) {}

    bool Collider::IsColided (GameObject* first, GameObject* second)
    {
        auto a = first->GetComponent<MeshRenderer> ();
        auto b = second->GetComponent<MeshRenderer> ();

        if (a == nullptr || b == nullptr)
            return false;

        auto c = a->triangles;
        auto d = b->triangles;

        if (c.size () == 0 || d.size () == 0)
            return false;

        bool result = false;

        for (auto e : c)
            for (auto f : d) result = result || IsIntersect (e.v, first->transform->GetGlobalMatrix (), f.v, second->transform->GetGlobalMatrix ());

        return result;
    }

    Collider::~Collider () {}

    void Collider::Awake () {}

    void Collider::Start () {}

    void Collider::onEnable () {}

    void Collider::onDisable () {}

    void Collider::onDestroy () {}
}
