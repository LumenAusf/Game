#include "gameobject.h"
#include <cxxabi.h>

namespace LumenAusf
{
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
