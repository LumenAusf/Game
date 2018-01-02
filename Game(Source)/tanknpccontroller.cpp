#include "tanknpccontroller.h"

using namespace LumenAusf;

TankNPCController::~TankNPCController () {}

void TankNPCController::Awake () { /*std::srand (unsigned(std::time (0)));*/}

void TankNPCController::Start () { playSoundFromMemory (SoundStartEngine, SDL_MIX_MAXVOLUME); }

void TankNPCController::Update ()
{
    //    int random_variable = std::rand ();
    //    std::cerr << std::to_string (random_variable) << std::endl;

    if (EventSystem::Key_Down)
    {
        Rotate (Arrows::Up);
        Move ();
    }

    if (EventSystem::Key_Up)
    {
        Rotate (Arrows::Down);
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

    if (EventSystem::Key_Space)
    {
        Fire ();
    }
}

void TankNPCController::onEnable () {}

void TankNPCController::onDisable () {}

void TankNPCController::onDestroy () {}

void TankNPCController::Fire () { playSoundFromMemory (SoundFire, SDL_MIX_MAXVOLUME); }

void TankNPCController::Rotate (Arrows dir)
{
    if (Direction != dir)
    {
        Direction = dir;
        gameObject->transform->setLocalRotation (mat2x3::rotation (1.57f * dir));
    }
}

void TankNPCController::Move ()
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

void TankNPCController::SetSounds (Audio* Start, Audio* Stay, Audio* Run, Audio* Fire)
{
    SoundStartEngine = Start;
    SoundEngine = Stay;
    SoundRun = Run;
    SoundFire = Fire;
}

void TankNPCController::Destroy () { this->~TankNPCController (); }
