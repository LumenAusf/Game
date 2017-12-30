#include "gameobject.h"

namespace LumenAusf
{
    mat2x3 Transform::getLocalScale () const { return localScale; }
    void Transform::setLocalScale (const mat2x3& value) { localScale = value; }

    mat2x3 Transform::getLocalRotation () const { return localRotation; }
    void Transform::setLocalRotation (const mat2x3& value) { localRotation = value; }

    mat2x3 Transform::getLocalPosition () const { return localPosition; }
    void Transform::setLocalPosition (const mat2x3& value) { localPosition = value; }

    mat2x3 Transform::getGlobalScale () const { return parent != nullptr ? localScale * parent->getGlobalScale () : localScale; }
    //    void Transform::setGlobalScale (const mat2x3& value) {}

    mat2x3 Transform::getGlobalRotation () const { return parent != nullptr ? localRotation * parent->getGlobalRotation () : localRotation; }
    //    void Transform::setGlobalRotation (const mat2x3& value) {}

    mat2x3 Transform::getGlobalPosition () const { return parent != nullptr ? localPosition * parent->getGlobalPosition () : localPosition; }
    //    void Transform::setGlobalPosition (const mat2x3& value) {}

    mat2x3 Transform::getAspect () const { return aspect; }
    void Transform::setAspect (const mat2x3& value) { aspect = value; }
}
