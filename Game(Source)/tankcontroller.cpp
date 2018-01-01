#include "tankcontroller.h"

using namespace LumenAusf;

TankController::~TankController () {}

void TankController::Awake () {}

void TankController::Start () { playSoundFromMemory (SoundStartEngine, SDL_MIX_MAXVOLUME); }

void TankController::Update ()
{
    if (EventSystem::Key_Down)
    {
        Rotate (Arrows::Down);
        Move ();
    }

    if (EventSystem::Key_Up)
    {
        Rotate (Arrows::Up);
        Move ();
    }

    if (EventSystem::Key_Left)
    {
        Rotate (Arrows::Left);
        Move ();
    }

    if (EventSystem::Key_Right)
    {
        Rotate (Arrows::Right);
        Move ();
    }

    if (EventSystem::Key_Space && !previousSpace)
    {
        Fire ();
    }

    previousSpace = EventSystem::Key_Space;
}

void TankController::onEnable () {}

void TankController::onDisable () {}

void TankController::onDestroy () {}

void TankController::Fire () { playSoundFromMemory (SoundFire, SDL_MIX_MAXVOLUME); }

void TankController::Rotate (Arrows dir)
{
    if (Direction != dir)
    {
        Direction = dir;
        gameObject->transform->setLocalRotation (mat2x3::rotation (1.57f * dir));
    }
}

void TankController::Move ()
{
    auto a = gameObject->GetComponent<MeshRenderer> ();
    if (a == nullptr)
        return;
    a->atlas->Next ();
    playSoundFromMemory (SoundRun, SDL_MIX_MAXVOLUME / 2);
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
}

void TankController::SetSounds (Audio* Start, Audio* Stay, Audio* Run, Audio* Fire)
{
    SoundStartEngine = Start;
    SoundEngine = Stay;
    SoundRun = Run;
    SoundFire = Fire;
}
