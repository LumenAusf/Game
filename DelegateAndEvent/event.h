
#ifndef EVENT_H
#define EVENT_H

#include "EventBase.h"

class Event: public EventBase
{
    public:

        Event& operator += (const Delegate &deleg)
        {
            Push(deleg);
            return *this;
        }

        Event& operator -= (const Delegate &deleg)
        {
            Remove(deleg);
            return *this;
        }

        void operator () ();

        template <class Arg>
        void operator() (Arg arg);

        template <class Arg1, class Arg2>
        void operator() (Arg1 arg1, Arg2 arg2);

};

inline void Event::operator ()()
{
    EventBase::Iterator *iter = GetIterator();
    Delegate d;

    while (iter->HasNext())
    {
        d = iter->GetNext();
        d();
    }

//    delete iter;
}

template <class Arg>
inline void Event::operator ()(Arg arg)
{
    EventBase::Iterator *iter = GetIterator();
    Delegate d;

    while (iter->HasNext())
    {
        d = iter->GetNext();
        d(arg);
    }

//    delete iter;
}

template <class Arg1, class Arg2>
inline void Event::operator ()(Arg1 arg1, Arg2 arg2)
{
    EventBase::Iterator *iter = GetIterator();
    Delegate d;

    while (iter->HasNext())
    {
        d = iter->GetNext();
        d(arg1, arg2);
    }

    delete iter;
}

#endif
