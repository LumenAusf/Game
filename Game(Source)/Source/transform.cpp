#include "gameobject.h"

namespace LumenAusf
{
    glm::vec3 Transform::getLocalScale () const { return scalevec; }
    void Transform::setLocalScale (const glm::vec3& value) { scalevec = value; }

    glm::vec3 Transform::getLocalRotation () const { return rotationvec; }
    void Transform::setLocalRotation (const glm::vec3& value) { rotationvec = value; }

    glm::vec3 Transform::getLocalPosition () const { return positionvec; }
    void Transform::setLocalPosition (const glm::vec3& value) { positionvec = value; }

    glm::vec3 Transform::getGlobalScale () const { return parent != nullptr ? parent->getGlobalScale () * scalevec : scalevec; }
    //    void Transform::setGlobalScale (const mat2x3& value) {}

    glm::vec3 Transform::getGlobalRotation () const
    {
        return parent != nullptr ? glm::translate (glm::mat4 (), parent->getGlobalRotation ()) * glm::vec4 (rotationvec, 1.f) : rotationvec;
    }
    //    void Transform::setGlobalRotation (const mat2x3& value) {}

    glm::vec3 Transform::getGlobalPosition () const
    {
        return parent != nullptr ? glm::translate (glm::mat4 (), parent->getGlobalPosition ()) * glm::vec4 (positionvec, 1.f) : positionvec;
    }
    //    void Transform::setGlobalPosition (const mat2x3& value) {}

    glm::mat4 Transform::GetGlobalMatrix ()
    {
        glm::mat4 trans;
        trans = glm::scale (trans, getGlobalScale ());
        trans = glm::translate (trans, getGlobalPosition ());
        //        trans = glm::rotate (trans, getGlobalRotation ().x, glm::vec3 (1.f, 0.f, 0.f));
        //        trans = glm::rotate (trans, getGlobalRotation ().y, glm::vec3 (0.f, 1.f, 0.f));
        //        trans = glm::rotate (trans, getGlobalRotation ().z, glm::vec3 (0.f, 0.f, 1.f));

        return trans;
    }

    glm::mat4 Transform::GetLocalMatrix ()
    {
        glm::mat4 trans;
        trans = glm::scale (trans, getLocalScale ());
        trans = glm::translate (trans, getLocalPosition ());
        //        trans = glm::rotate (trans, getLocalRotation ().x, glm::vec3 (1.f, 0.f, 0.f));
        //        trans = glm::rotate (trans, getLocalRotation ().y, glm::vec3 (0.f, 1.f, 0.f));
        //        trans = glm::rotate (trans, getLocalRotation ().z, glm::vec3 (0.f, 0.f, 1.f));

        return trans;
    }

    void Transform::SetPosition (glm::vec3 pos) { positionvec = pos; }
}
