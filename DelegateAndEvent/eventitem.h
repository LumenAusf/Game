#ifndef EVENTITEM_H
#define EVENTITEM_H

#include <iostream>

namespace lumenausf
{
    enum TYPE_EVENT
    {
        //Keyboard
        TYPENONE,
        KEYDOWN,
        KEYUP,
        TEXTEDITING,
        TEXTINPUT,
        KEYMAPCHANGED,

        //Mouse
        MOUSEMOTION,
        MOUSEBUTTONDOWN,
        MOUSEBUTTONUP,
        MOUSEWHEEL,
    };

    enum KEY_CODE
    {
        KEYNONE,
        RIGHT,
        LEFT,
        DOWN,
        UP,
    };

    class EventItem
    {
        public:
            EventItem(){}
            ~EventItem(){}
            void Test(){
                std::clog << "Hop" << std::endl;
            }

            TYPE_EVENT typeEvent = TYPENONE;
            KEY_CODE keyCode = KEYNONE;
    };
}
#endif // EVENTITEM_H
