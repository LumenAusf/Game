#include "tankcontroller.h"

using namespace LumenAusf;

TankController::~TankController () { std::cerr << "removed \"TankController\" from " + gameObject->name << std::endl; }

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

void TankController::Fire ()
{
    playSoundFromMemory (SoundFire, SDL_MIX_MAXVOLUME);
    std::string config = "configurations/MissileData.txt";
    new Missile (gameObject, config, textureForMissile, true);
}

void TankController::Rotate (Arrows dir)
{
    if (Direction != dir)
    {
        Direction = dir;
        gameObject->transform->setLocalRotation (glm::vec3 (0.0f, 0.0f, 90.f * dir));
    }
}

void TankController::Move ()
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
            if (!gameObject->CanMove (glm::vec3 (0.f, speed, 0.f)))
                break;
            gameObject->transform->setLocalPosition (gameObject->transform->getLocalPosition () + glm::vec3 (0.f, speed, 0.f));
            break;
        case Arrows::Down:
            if (!gameObject->CanMove (glm::vec3 (0.f, -speed, 0.f)))
                break;
            gameObject->transform->setLocalPosition (gameObject->transform->getLocalPosition () + glm::vec3 (0.f, -speed, 0.f));
            break;
        case Arrows::Right:
            if (!gameObject->CanMove (glm::vec3 (speed, 0.f, 0.f)))
                break;
            gameObject->transform->setLocalPosition (gameObject->transform->getLocalPosition () +
                                                     glm::vec3 (speed / gameObject->transform->getAspect (), 0.f, 0.f));
            break;
        case Arrows::Left:
            if (!gameObject->CanMove (glm::vec3 (-speed, 0.f, 0.f)))
                break;
            gameObject->transform->setLocalPosition (gameObject->transform->getLocalPosition () +
                                                     glm::vec3 (-speed / gameObject->transform->getAspect (), 0.f, 0.f));
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

void TankController::SetTextureMissile (Texture* tex) { textureForMissile = tex; }

void TankController::Destroy () { this->~TankController (); }
