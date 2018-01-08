#include "gameobject.h"

namespace LumenAusf
{
    glm::mat4 Transform::getLocalScale () const { return scale; }
    void Transform::setLocalScale (const glm::mat4& value) { scale = value; }

    glm::mat4 Transform::getLocalRotation () const { return rotation; }
    void Transform::setLocalRotation (const glm::mat4& value) { rotation = value; }

    glm::mat4 Transform::getLocalPosition () const { return position; }
    void Transform::setLocalPosition (const glm::mat4& value) { position = value; }

    glm::mat4 Transform::getGlobalScale () const { return parent != nullptr ? scale * parent->getGlobalScale () : scale; }
    //    void Transform::setGlobalScale (const mat2x3& value) {}

    glm::mat4 Transform::getGlobalRotation () const { return parent != nullptr ? rotation * parent->getGlobalRotation () : rotation; }
    //    void Transform::setGlobalRotation (const mat2x3& value) {}

    glm::mat4 Transform::getGlobalPosition () const { return parent != nullptr ? position * parent->getGlobalPosition () : position; }
    //    void Transform::setGlobalPosition (const mat2x3& value) {}
}
