#include <iostream>

#include "s_game.h"

int main()
{
    try
    {
        S_game game(64);
        game.start(30020, true);
        std::cin.get();
        game.stop();
    }
    catch (const std::system_error& e)
    {
        std::cerr << e.what() << '\n';
    }
}