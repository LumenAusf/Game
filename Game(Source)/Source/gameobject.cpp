#include "gameobject.h"
#include <cxxabi.h>
#include "collider.h"

namespace LumenAusf
{
    std::vector<GameObject*> GameObject::objects = std::vector<GameObject*> ();

    void GameObject::UpdateAll ()
    {
        for (auto a : objects)
            if (a->enabled)
                for (auto b : a->components)
                    if (b->getEnabled ())
                        b->Update ();
    }

    void GameObject::AwakeAll ()
    {
        for (auto a : objects)
            if (a->enabled)
                for (auto b : a->components)
                    if (b->getEnabled ())
                        b->Awake ();
    }

    void GameObject::StartAll ()
    {
        for (auto a : objects)
            if (a->enabled)
                for (auto b : a->components)
                    if (b->getEnabled ())
                        b->Start ();
    }

    void GameObject::FixedUpdateAll ()
    {
        for (unsigned int a = 0; a < objects.size () - 1; a++)
        {
            if (objects[a]->GetComponent<Collider> () != nullptr)
                for (auto b = a + 1; b < objects.size (); b++)
                {
                    if (objects[b]->GetComponent<Collider> () != nullptr)
                        if (Collider::IsColided (objects[a], objects[b]))
                            std::cerr << objects[a]->name << " ::: " << objects[b]->name << std::endl;
                }
        }
    }

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
