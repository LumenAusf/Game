#include <cstdlib>
#include <iostream>
#include "engine.h"
#include <exception>

class Play
{
    public:
        void Run()
        {
            try
            {
                lumenausf::Engine * Engine = new lumenausf::Engine();
                Engine->Init();
                Engine->EngineEvent += Delegate(this, &Play::EventGetted);
                Engine->ReadEvent();
                Engine->Finish();
            }catch(std::exception ex)
            {
                std::cerr << ex.what();
                exit(EXIT_FAILURE);
            }
        }

        void EventGetted(lumenausf::EventItem item)
        {
            if(item.typeEvent == lumenausf::TYPE_EVENT::KEYDOWN)
            {
                switch (item.keyCode) {
                    case lumenausf::KEY_CODE::DOWN:
                        std::clog << "DOWN" << std::endl;
                    break;
                    case lumenausf::KEY_CODE::RIGHT:
                        std::clog << "RIGHT" << std::endl;
                    break;
                    case lumenausf::KEY_CODE::UP:
                        std::clog << "UP" << std::endl;
                    break;
                    case lumenausf::KEY_CODE::LEFT:
                        std::clog << "LEFT" << std::endl;
                    break;
                    default:
                    break;
                }
            }
        }
};

int main()
{
    Play game = Play();
    game.Run();
    return EXIT_SUCCESS;
}
