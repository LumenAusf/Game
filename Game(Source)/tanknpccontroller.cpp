#include "tanknpccontroller.h"

using namespace LumenAusf;

TankNPCController::~TankNPCController () { std::cerr << "removed \"TankNPCController\" from " + gameObject->name << std::endl; }

void TankNPCController::Awake () { /*std::srand (unsigned(std::time (0)));*/}

void TankNPCController::Start () { playSoundFromMemory (SoundStartEngine, SDL_MIX_MAXVOLUME); }

void TankNPCController::Update ()
{
    //    std::srand (unsigned(std::time (0)));
    //    float random_variable = std::rand () * 1.f / RAND_MAX * 1.f;
    //    int change = (int)((std::rand () * 1.f / (RAND_MAX * 1.f / 100))) % 100;
    //    std::cerr << std::endl << std::to_string (change) << std::endl;

    GameObject* gogo = nullptr;
    for (auto gop : GameObject::objects)
    {
        if (gop == nullptr)
            continue;
        if (gop->GetComponent<TankController> () != nullptr)
        {
            gogo = gop;
            break;
        }
    }

    if (gogo == nullptr)
        return;

    //    if (gameObject->transform->getGlobalPosition ().delta.x - gogo->transform->getGlobalPosition ().delta.x > 0.001f)
    //    {
    //        Rotate (Arrows::Left);
    //        Move ();
    //    }
    //    else if (gameObject->transform->getGlobalPosition ().delta.x - gogo->transform->getGlobalPosition ().delta.x < -0.001f)
    //    {
    //        Rotate (Arrows::Right);
    //        Move ();
    //    }
    //    else if (gameObject->transform->getGlobalPosition ().delta.y - gogo->transform->getGlobalPosition ().delta.y > 0.001f)
    //    {
    //        Rotate (Arrows::Down);
    //        Move ();
    //    }
    //    else if (gameObject->transform->getGlobalPosition ().delta.y - gogo->transform->getGlobalPosition ().delta.y < -0.001f)
    //    {
    //        Rotate (Arrows::Up);
    //        Move ();
    //    }

    //    if (change > 2)
    //    {
    //        Move ();
    //        return;
    //    }

    //    if (random_variable > 0.7f)
    //    {
    //        Rotate (Arrows::Down);
    //        Move ();
    //    }
    //    else if (random_variable > 0.5f)
    //    {
    //        Rotate (Arrows::Left);
    //        Move ();
    //    }
    //    else if (random_variable > 0.25f)
    //    {
    //        Rotate (Arrows::Up);
    //        Move ();
    //    }
    //    else
    //    {
    //        Rotate (Arrows::Right);
    //        Move ();
    //    }

    float random_variable = std::rand () * 1.f / RAND_MAX * 1.f;
    if (random_variable > .99f)
        Fire ();

    //    if (EventSystem::Key_Down)
    //    {
    //        Rotate (Arrows::Up);
    //        Move ();
    //    }

    //    if (EventSystem::Key_Up)
    //    {
    //        Rotate (Arrows::Down);
    //        Move ();
    //    }

    //    if (EventSystem::Key_Left)
    //    {
    //        Rotate (Arrows::Left);
    //        Move ();
    //    }

    //    if (EventSystem::Key_Right)
    //    {
    //        Rotate (Arrows::Right);
    //        Move ();
    //    }

    //    if (EventSystem::Key_Space && !previousSpace)
    //    {
    //        Fire ();
    //    }

    //    previousSpace = EventSystem::Key_Space;
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
        //        gameObject->transform->setLocalRotation (mat2x3::rotation (1.57079632679f * dir));
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

    //    switch (Direction)
    //    {
    //        case Arrows::Up:
    //            if (!gameObject->CanMove (vec2 (0.f, speed)))
    //                break;
    //            gameObject->transform->setLocalPosition (gameObject->transform->getLocalPosition () * mat2x3::move (vec2 (0.f, speed)));
    //            break;
    //        case Arrows::Down:
    //            if (!gameObject->CanMove (vec2 (0.f, -speed)))
    //                break;
    //            gameObject->transform->setLocalPosition (gameObject->transform->getLocalPosition () * mat2x3::move (vec2 (0.f, -speed)));
    //            break;
    //        case Arrows::Right:
    //            if (!gameObject->CanMove (vec2 (speed, 0.f)))
    //                break;
    //            gameObject->transform->setLocalPosition (gameObject->transform->getLocalPosition () * mat2x3::move (vec2 (speed, 0.f)));
    //            break;
    //        case Arrows::Left:
    //            if (!gameObject->CanMove (vec2 (-speed, 0.f)))
    //                break;
    //            gameObject->transform->setLocalPosition (gameObject->transform->getLocalPosition () * mat2x3::move (vec2 (-speed, 0.f)));
    //            break;
    //    }
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
