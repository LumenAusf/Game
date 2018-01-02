#include "missilecontroller.h"

using namespace LumenAusf;

MissileController::~MissileController () { std::cerr << "removed missile controller from " + gameObject->name << std::endl; }

void MissileController::Awake () {}

void MissileController::Start () {}

void MissileController::Update ()
{
    auto a = gameObject->GetComponent<MeshRenderer> ();
    if (a == nullptr)
        return;
    playSoundFromMemory (SoundRun, SDL_MIX_MAXVOLUME / 4);
    switch (Direction)
    {
        case Arrows::Up:
            gameObject->transform->setLocalPosition (gameObject->transform->getLocalPosition () * mat2x3::move (vec2 (0.f, Speed)));
            break;
        case Arrows::Down:
            gameObject->transform->setLocalPosition (gameObject->transform->getLocalPosition () * mat2x3::move (vec2 (0.f, -Speed)));
            break;
        case Arrows::Right:
            gameObject->transform->setLocalPosition (gameObject->transform->getLocalPosition () * mat2x3::move (vec2 (Speed, 0.f)));
            break;
        case Arrows::Left:
            gameObject->transform->setLocalPosition (gameObject->transform->getLocalPosition () * mat2x3::move (vec2 (-Speed, 0.f)));
            break;
    }
    if (gameObject->transform->getGlobalPosition ().delta.x < -1 || gameObject->transform->getGlobalPosition ().delta.x > 1 ||
        gameObject->transform->getGlobalPosition ().delta.y < -1 || gameObject->transform->getGlobalPosition ().delta.y > 1)
        gameObject->~GameObject ();
}

void MissileController::onEnable () {}

void MissileController::onDisable () {}

void MissileController::onDestroy () {}

void MissileController::SetSounds (Audio* r, Audio* f)
{
    SoundRun = r;
    SoundFire = f;
}

void MissileController::Destroy () { this->~MissileController (); }
