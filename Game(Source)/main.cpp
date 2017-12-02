#include <algorithm>
#include <array>
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <memory>
#include <string_view>

#include "Source/engine.h"

class Play
{
   public:
    void Run ()
    {
        try
        {
            Engine = new LumenAusf::Engine ();
            running = true;
            Engine->Init ();
            Engine->EngineEvent += Delegate (this, &Play::EventGetted);
            while (running) Engine->ReadEvent ();
            Engine->Finish ();
        }
        catch (std::exception ex)
        {
            std::cerr << ex.what ();
            exit (EXIT_FAILURE);
        }
    }

    void EventGetted (LumenAusf::EventItem item)
    {
        switch (item.typeEvent)
        {
            case LumenAusf::TYPE_EVENT::KEYDOWN:
                switch (item.keyCode)
                {
                    case LumenAusf::KEY_CODE::ESCAPE:
                        running = false;
                        break;
                    case LumenAusf::KEY_CODE::DOWN:
                        std::clog << "DOWN" << std::endl;
                        break;
                    case LumenAusf::KEY_CODE::RIGHT:
                        std::clog << "RIGHT" << std::endl;
                        break;
                    case LumenAusf::KEY_CODE::UP:
                        std::clog << "UP" << std::endl;
                        break;
                    case LumenAusf::KEY_CODE::LEFT:
                        std::clog << "LEFT" << std::endl;
                        break;
                    case LumenAusf::KEY_CODE::SPACE:
                    {
                        std::ifstream file ("vertexes.txt");
                        assert (!!file);
                        LumenAusf::triangle tr;
                        file >> tr;
                        if (Engine->DrawTriangle (tr))
                            std::clog << "Ok" << std::endl;
                        else
                            std::clog << "failed" << std::endl;
                        break;
                    }
                    default:
                        break;
                }
                break;
            case LumenAusf::TYPE_EVENT::QUIT:
                running = false;
                break;
            default:

                break;
        }
    }

   private:
    bool running;
    LumenAusf::Engine *Engine;
};

int main ()
{
    Play game = Play ();
    game.Run ();
    return EXIT_SUCCESS;
}
