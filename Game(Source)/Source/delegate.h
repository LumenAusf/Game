#pragma once

#ifndef DELEGATE_H
#define DELEGATE_H



class Delegate
{
private:

        struct X {};
        typedef void (X::*Func)();

        X *_ptr;
        Func _func;

public:

        Delegate()
                : _ptr(0), _func(0)
        {
        }

        template <class Owner>
                Delegate(Owner *owner, void (Owner::*func)())
                : _ptr(0), _func(0)
        {
                _func = reinterpret_cast<Func>(func);
                _ptr = reinterpret_cast<X *>(owner);
        }

        template <class Owner, class Arg>
                Delegate(Owner *owner, void (Owner::*func)(Arg))
        {
                _func = reinterpret_cast<Func>(func);
                _ptr = reinterpret_cast<X *>(owner);
        }

        template <class Owner, class Arg1, class Arg2>
                Delegate(Owner *owner, void (Owner::*func)(Arg1, Arg2))
        {
                _func = reinterpret_cast<Func>(func);
                _ptr = reinterpret_cast<X *>(owner);
        }

        bool operator ! ()
        {
                return (!_ptr || !_func);
        }

        bool operator == (const Delegate &delegate)
        {
                return (_ptr == delegate._ptr && _func == delegate._func);
        }

        bool operator != (const Delegate &delegate)
        {
                return !(*this == delegate);
        }

        void operator () ();

        template <class Arg>
                void operator() (Arg arg);

        template <class Arg1, class Arg2>
                void operator() (Arg1 arg1, Arg2 arg2);

};


inline void Delegate::operator () ()
{
        if (_ptr && _func)
                (_ptr->*_func)();
}

template <class Arg>
void Delegate::operator () (Arg arg)
{
        typedef void (X::*Mfn)(Arg);
        Mfn func = reinterpret_cast<Mfn>(_func);

        if (_ptr && func)
                (_ptr->*func)(arg);
}

template <class Arg1, class Arg2>
void Delegate::operator () (Arg1 arg1, Arg2 arg2)
{
        typedef void (X::*Mfn)(Arg1, Arg2);
        Mfn func = reinterpret_cast<Mfn>(_func);

        if (_ptr && func)
                (_ptr->*func)(arg1, arg2);
}


#endif
