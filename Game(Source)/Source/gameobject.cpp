#include "gameobject.h"
#include <cxxabi.h>
#include "collider.h"

namespace LumenAusf
{
    std::vector<GameObject*> GameObject::objects = std::vector<GameObject*> ();

    GameObject::GameObject (std::string name)
    {
        transform = new Transform ();
        transform->parent = nullptr;
        objects.push_back (this);
        this->name = name != "" ? name : this->name;
    }

    GameObject::GameObject (Transform* parent, std::string name)
    {
        transform = new Transform ();
        transform->parent = parent;
        if (parent != nullptr)
            parent->children.push_back (transform);
        objects.push_back (this);
        this->name = name != "" ? name : this->name;
    }

    GameObject::~GameObject ()
    {
        auto a = std::find (objects.begin (), objects.end (), this);
        (*a) = nullptr;

        OnDestroy ();

        for (auto b : components)
        {
            b->Destroy ();
        }

        std::cerr << "Delete gameObject " + name + " ::: Count of objects: " << objects.size () << std::endl;
    }

    void GameObject::UpdateAll ()
    {
        for (auto a : objects)
        {
            if (a == nullptr || !a->enabled)
                continue;

            for (auto b : a->components)
            {
                if (a != nullptr && b != nullptr && b->getEnabled ())
                    b->Update ();
                if (a == nullptr)
                    break;
            }
        }

        for (auto a = objects.end () - 1; a != objects.begin (); a--)
        {
            if ((*a) == nullptr)
            {
                objects.erase (a);
            }
        }
        if ((*objects.begin ()) == nullptr)
            objects.erase (objects.begin ());
    }

    void GameObject::AwakeAll ()
    {
        objects.reserve (512);
        for (auto a : objects)
            if (a != nullptr && a->enabled)
                for (auto b : a->components)
                    if (b != nullptr && b->getEnabled ())
                        b->Awake ();
    }

    void GameObject::StartAll ()
    {
        for (auto a : objects)
            if (a != nullptr && a->enabled)
                for (auto b : a->components)
                    if (b != nullptr && b->getEnabled ())
                        b->Start ();
    }

    void GameObject::FixedUpdateAll ()
    {
        try
        {
            for (unsigned int a = 0; a < objects.size () - 1; a++)
            {
                if (objects[a] != nullptr && objects[a]->GetComponent<Collider> () != nullptr)
                    for (auto b = a + 1; b < objects.size (); b++)
                    {
                        if (objects[b] != nullptr && objects[b]->GetComponent<Collider> () != nullptr)
                            if (Collider::IsColided (objects[a], objects[b]))
                            {
                                if ((objects[a]->tag == "Block" && objects[b]->tag == "Missile") ||
                                    (objects[b]->tag == "Block" && objects[a]->tag == "Missile") ||
                                    (objects[a]->tag == "Block" && objects[b]->tag == "MissileNPC") ||
                                    (objects[b]->tag == "Block" && objects[a]->tag == "MissileNPC") ||
                                    (objects[a]->tag == "TankNPC" && objects[b]->tag == "Missile") ||
                                    (objects[a]->tag == "Missile" && objects[b]->tag == "TankNPC") ||
                                    (objects[b]->tag == "TankUser" && objects[a]->tag == "MissileNPC") ||
                                    (objects[b]->tag == "MissileNPC" && objects[a]->tag == "TankUser"))
                                {
                                    std::cerr << objects[a]->name << " ::: " << objects[b]->name << " ||||| " << objects[a]->tag
                                              << " ::: " << objects[b]->tag << std::endl;
                                    objects[b]->OnDestroy ();
                                    objects[a]->OnDestroy ();
                                    objects[b]->~GameObject ();
                                    objects[a]->~GameObject ();
                                    break;
                                }
                            }
                    }
            }
        }
        catch (std::exception ex)
        {
            std::cerr << ex.what ();
        }
    }

    void GameObject::OnDestroy ()
    {
        for (auto a : components)
            if (a != nullptr)
                a->onDestroy ();
    }

    bool GameObject::CanMove (glm::vec3 pos)
    {
        auto result = true;
        try
        {
            for (unsigned int a = 0; a < objects.size (); a++)
            {
                if (objects[a] != nullptr && objects[a] != this && objects[a]->GetComponent<Collider> () != nullptr)
                {
                    if ((objects[a]->tag == "Block" && tag == "TankUser") || (objects[a]->tag == "Block" && tag == "TankNPC") ||
                        (objects[a]->tag == "TankNPC" && tag == "TankUser") || (tag == "TankNPC" && objects[a]->tag == "TankUser"))
                    {
                        MeshRenderer* b = objects[a]->GetComponent<MeshRenderer> ();
                        MeshRenderer* c = GetComponent<MeshRenderer> ();

                        if (b == nullptr || c == nullptr)
                            continue;
                        std::vector<trianglePTC> d = b->triangles;
                        std::vector<trianglePTC> e = c->triangles;
                        if (e.size () == 0 || d.size () == 0)
                            continue;
                        glm::mat4 f = objects[a]->transform->GetGlobalMatrix ();
                        glm::mat4 g = glm::translate (transform->GetGlobalMatrix (), pos);
                        result = result && Collider::CanSetSo (d, f, e, g);
                    }
                }
            }
        }
        catch (std::exception ex)
        {
            std::cerr << ex.what ();
        }
        return result;
    }

    //    glm::mat4 Transform::GetGlobalMatrix() { return getGlobalPosition () * getGlobalRotation () * getGlobalScale (); }

    //    glm::mat4 Transform::GetLocalMatrix() { return getLocalPosition () * getLocalRotation () * getLocalScale (); }

    //    void Transform::SetPosition(glm::vec3 pos) { position = glm::translate (glm::mat4 (1.f), pos); }

    //    void GameObject::RenderAll ()
    //    {
    //        for (auto go : objects)
    //        {
    //            if (go == nullptr)
    //                return;

    //            auto b = go->GetComponent<LumenAusf::MeshRenderer> ();
    //            if (b == nullptr || !b->getEnabled ())
    //                continue;

    //            if (b->triangles.size () == 0)
    //                continue;

    //            for (unsigned long i = 0; i < b->triangles.size (); i++)
    //            {
    //                engine->DrawTriangle (b->triangles.at (i), b->texture, go->transform->GetGlobalMatrix ());
    //            }
    //        }
    //    }

    //    mat2x3 Transform::getLocalScale () const { return localScale; }

    //    void Transform::setLocalScale (const mat2x3& value) { localScale = value; }

    //    mat2x3 Transform::getLocalRotation () const { return localRotation; }

    //    void Transform::setLocalRotation (const mat2x3& value) { localRotation = value; }

    //    mat2x3 Transform::getLocalPosition () const { return localPosition; }

    //    void Transform::setLocalPosition (const mat2x3& value) { localPosition = value; }

    //    mat2x3 Transform::getGlobalScale () const { return globalScale; }

    //    void Transform::setGlobalScale (const mat2x3& value) { globalScale = value; }

    //    mat2x3 Transform::getGlobalRotation () const { return globalRotation; }

    //    void Transform::setGlobalRotation (const mat2x3& value) { globalRotation = value; }

    //    mat2x3 Transform::getGlobalPosition () const { return globalPosition; }

    //    void Transform::setGlobalPosition (const mat2x3& value) { globalPosition = value; }

    //    mat2x3 Transform::getAspect () const { return aspect; }

    //    void Transform::setAspect (const mat2x3& value) { aspect = value; }

    //    template<typename T>
    //    Component* GameObject::AddComponent (T component)
    //    {
    //        bool Finded = false;
    //        for (size_t i = 0; i < components.size (); i++)
    //        {
    //            std::cout << abi::__cxa_demangle (typeid (*component).name (), 0, 0, new int);
    //            if (typeid (*(components.at (i))) == typeid (*component))
    //            {
    //                Finded = true;
    //                break;
    //            }
    //        }
    //        if (Finded)
    //        {
    //            throw new std::exception ();
    //        }
    //        std::cout << typeid (*component).name () << std::endl;
    //        components.push_back (component);
    //        return component;
    //    }

    //    Component* GameObject::GetOrAddComponent (Component* component)
    //    {
    //        bool Finded = false;
    //        Component* temp = nullptr;
    //        for (size_t i = 0; i < components.size (); i++)
    //        {
    //            if (typeid (*(components.at (i))) == typeid (*component))
    //            {
    //                Finded = true;
    //                temp = components.at (i);
    //                break;
    //            }
    //        }
    //        if (Finded)
    //        {
    //            return temp;
    //        }
    //        components.push_back (component);
    //        return component;
    //    }

    //    Component* GameObject::GetComponent (Component* component)
    //    {
    //        Component* temp = nullptr;
    //        for (size_t i = 0; i < components.size (); i++)
    //        {
    //            if (typeid (*(components.at (i))).name () == typeid (*component).name ())
    //            {
    //                temp = components.at (i);
    //                break;
    //            }
    //        }
    //        return temp;
    //    }

    //    void GameObject::RemoveComponent (Component* component)
    //    {
    //        for (size_t i = 0; i < components.size (); i++)
    //        {
    //            if (typeid (*(components.at (i))) == typeid (*component))
    //            {
    //                components.erase (components.cbegin () + static_cast<long> (i));
    //                break;
    //            }
    //        }
    //    }
}
