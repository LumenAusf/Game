#include "tank.h"

void Tank::Start () { playSoundFromMemory (SoundStartEngine, SDL_MIX_MAXVOLUME / 2); }

void Tank::Rotate (Arrows dir)
{
    if (Direction != dir)
    {
        Direction = dir;
        transform.rotation = LumenAusf::mat2x3::rotation (1.57f * dir);
    }
}

void Tank::Move ()
{
    Next ();
    playSoundFromMemory (SoundRun, SDL_MIX_MAXVOLUME / 2);
    switch (Direction)
    {
        case Arrows::Up:
            transform.position *= LumenAusf::mat2x3::move (LumenAusf::vec2 (0.f, Speed));
            break;
        case Arrows::Down:
            transform.position *= LumenAusf::mat2x3::move (LumenAusf::vec2 (0.f, -Speed));
            break;
        case Arrows::Right:
            transform.position *= LumenAusf::mat2x3::move (LumenAusf::vec2 (Speed, 0.f));
            break;
        case Arrows::Left:
            transform.position *= LumenAusf::mat2x3::move (LumenAusf::vec2 (-Speed, 0.f));
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
