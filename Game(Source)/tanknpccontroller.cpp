#include "tanknpccontroller.h"

using namespace LumenAusf;

TankNPCController::~TankNPCController () { std::cerr << "removed \"TankNPCController\" from " + gameObject->name << std::endl; }

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

    if (EventSystem::Key_Space && !previousSpace)
    {
        Fire ();
    }

    previousSpace = EventSystem::Key_Space;
}

void TankNPCController::onEnable () {}

void TankNPCController::onDisable () {}

void TankNPCController::onDestroy () {}

void TankNPCController::Fire ()
{
    playSoundFromMemory (SoundFire, SDL_MIX_MAXVOLUME);
    std::string config = "configurations/MissileData.txt";
    new Missile (gameObject, config, textureForMissile, false);
}

void TankNPCController::Rotate (Arrows dir)
{
    if (Direction != dir)
    {
        Direction = dir;
        gameObject->transform->setLocalRotation (mat2x3::rotation (1.57079632679f * dir));
    }
}

void TankNPCController::Move ()
{
    auto a = gameObject->GetComponent<MeshRenderer> ();
    if (a == nullptr)
        return;
    a->atlas->Next ();
    auto speed = Speed * Engine::getDeltaTime () * 0.001f;
    playSoundFromMemory (SoundRun, SDL_MIX_MAXVOLUME / 5);

    switch (Direction)
    {
        case Arrows::Up:
            if (!gameObject->CanMove (vec2 (0.f, speed)))
                break;
            gameObject->transform->setLocalPosition (gameObject->transform->getLocalPosition () * mat2x3::move (vec2 (0.f, speed)));
            break;
        case Arrows::Down:
            if (!gameObject->CanMove (vec2 (0.f, -speed)))
                break;
            gameObject->transform->setLocalPosition (gameObject->transform->getLocalPosition () * mat2x3::move (vec2 (0.f, -speed)));
            break;
        case Arrows::Right:
            if (!gameObject->CanMove (vec2 (speed, 0.f)))
                break;
            gameObject->transform->setLocalPosition (gameObject->transform->getLocalPosition () * mat2x3::move (vec2 (speed, 0.f)));
            break;
        case Arrows::Left:
            if (!gameObject->CanMove (vec2 (-speed, 0.f)))
                break;
            gameObject->transform->setLocalPosition (gameObject->transform->getLocalPosition () * mat2x3::move (vec2 (-speed, 0.f)));
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

void TankNPCController::SetTextureMissile (Texture* tex) { textureForMissile = tex; }

void TankNPCController::Destroy () { this->~TankNPCController (); }
