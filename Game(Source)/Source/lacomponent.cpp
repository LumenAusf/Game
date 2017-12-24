#include "lacomponent.h"

namespace LumenAusf
{
    bool LAComponent::getEnabled () const { return enabled; }

    void LAComponent::setEnabled (bool value) { enabled = value; }

    GameObject* LAComponent::getGameObject () const { return gameObject; }

    void LAComponent::setGameObject (GameObject* value) { gameObject = value; }
}
