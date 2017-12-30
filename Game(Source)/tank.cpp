#include "tank.h"

int Tank::num = 0;

void Tank::Start () { playSoundFromMemory (SoundStartEngine, SDL_MIX_MAXVOLUME / 2); }

void Tank::Rotate (Arrows dir)
{
    if (Direction != dir)
    {
        Direction = dir;
        go->transform->setLocalRotation (LumenAusf::mat2x3::rotation (1.57f * dir));
    }
}

void Tank::Move ()
{
    auto a = go->GetComponent<LumenAusf::MeshRenderer> ();
    if (a == nullptr)
        return;
    a->atlas->Next ();
    playSoundFromMemory (SoundRun, SDL_MIX_MAXVOLUME / 2);
    switch (Direction)
    {
        case Arrows::Up:
            go->transform->setLocalPosition (go->transform->getLocalPosition () * LumenAusf::mat2x3::move (LumenAusf::vec2 (0.f, Speed)));
            break;
        case Arrows::Down:
            go->transform->setLocalPosition (go->transform->getLocalPosition () * LumenAusf::mat2x3::move (LumenAusf::vec2 (0.f, -Speed)));
            break;
        case Arrows::Right:
            go->transform->setLocalPosition (go->transform->getLocalPosition () * LumenAusf::mat2x3::move (LumenAusf::vec2 (Speed, 0.f)));
            break;
        case Arrows::Left:
            go->transform->setLocalPosition (go->transform->getLocalPosition () * LumenAusf::mat2x3::move (LumenAusf::vec2 (-Speed, 0.f)));
            break;
    }
}

float Tank::getSpeed () const { return Speed; }

void Tank::setSpeed (float value) { Speed = value; }

int Tank::getMissileCount () const { return MissileCount; }

void Tank::setMissileCount (int value) { MissileCount = value; }

void Tank::setMissile (Missile* pref) { MissilePref = pref; }

void Tank::SetSounds (Audio* Start, Audio* Stay, Audio* Run, Audio* Fire)
{
    SoundStartEngine = Start;
    SoundEngine = Stay;
    SoundRun = Run;
    SoundFire = Fire;
}
