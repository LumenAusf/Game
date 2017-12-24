#include "play.h"

int main ()
{
    Play game = Play ();

    try
    {
        game.Run ();
    }
    catch (std::exception ex)
    {
        std::cerr << ex.what () << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
