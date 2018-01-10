#include "missilecontroller.h"

using namespace LumenAusf;

MissileController::~MissileController () { std::cerr << "removed \"MissileController\" from " + gameObject->name << std::endl; }

void MissileController::Awake () {}

void MissileController::Start () {}

void MissileController::Update ()
{
    auto a = gameObject->GetComponent<MeshRenderer> ();
    if (a == nullptr)
        return;
    auto speed = Speed * Engine::getDeltaTime () * 0.001f;
    playSoundFromMemory (SoundRun, SDL_MIX_MAXVOLUME / 18);
    switch (Direction)
    {
        case Arrows::Up:
            gameObject->transform->setLocalPosition (gameObject->transform->getLocalPosition () += glm::vec3 (0.f, speed, 0.f));
            break;
        case Arrows::Down:
            gameObject->transform->setLocalPosition (gameObject->transform->getLocalPosition () += glm::vec3 (0.f, -speed, 0.f));
            break;
        case Arrows::Right:
            gameObject->transform->setLocalPosition (gameObject->transform->getLocalPosition () +=
                                                     glm::vec3 (speed / gameObject->transform->getAspect (), 0.f, 0.f));
            break;
        case Arrows::Left:
            gameObject->transform->setLocalPosition (gameObject->transform->getLocalPosition () +=
                                                     glm::vec3 (-speed / gameObject->transform->getAspect (), 0.f, 0.f));
            break;
    }
    //    if (gameObject->transform->getGlobalPosition (). .delta.x < -1 || gameObject->transform->getGlobalPosition ().delta.x > 1 ||
    //        gameObject->transform->getGlobalPosition ().delta.y < -1 || gameObject->transform->getGlobalPosition ().delta.y > 1)
    //        gameObject->~GameObject ();
}

void MissileController::onEnable () {}

void MissileController::onDisable () {}

void MissileController::onDestroy ()
{
    std::cerr << "misileDestroy" << std::endl;
    playSoundFromMemory (SoundFire, SDL_MIX_MAXVOLUME);
}

void MissileController::SetSounds (Audio* r, Audio* f)
{
    SoundRun = r;
    SoundFire = f;
}

void MissileController::Destroy () { this->~MissileController (); }
