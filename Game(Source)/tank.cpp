#include "tank.h"

void Tank::Start () { playSoundFromMemory (SoundStartEngine, SDL_MIX_MAXVOLUME / 2); }

void Tank::Rotate (Arrows dir)
{
    if (Direction != dir)
    {
        Direction = dir;
        go->transform->globalRotation = LumenAusf::mat2x3::rotation (1.57f * dir);
    }
}

void Tank::Move ()
{
    auto a = go->GetComponent(new LumenAusf::MeshRenderer());
    if(a == nullptr) return;
    auto b = static_cast<LumenAusf::MeshRenderer *>(a);
    if(b == nullptr) return;
    b->atlas->Next ();
    playSoundFromMemory (SoundRun, SDL_MIX_MAXVOLUME / 2);
    switch (Direction)
    {
        case Arrows::Up:
            go->transform->globalPosition *= LumenAusf::mat2x3::move (LumenAusf::vec2 (0.f, Speed));
            break;
        case Arrows::Down:
            go->transform->globalPosition *= LumenAusf::mat2x3::move (LumenAusf::vec2 (0.f, -Speed));
            break;
        case Arrows::Right:
            go->transform->globalPosition *= LumenAusf::mat2x3::move (LumenAusf::vec2 (Speed, 0.f));
            break;
        case Arrows::Left:
            go->transform->globalPosition *= LumenAusf::mat2x3::move (LumenAusf::vec2 (-Speed, 0.f));
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
