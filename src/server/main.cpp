#include <iostream>

#include "s_game.h"

int main()
{
    try
    {
        S_game game;
        game.start(30020, true);
        std::cin.get();
        game.stop();
        std::cin.get();
    }
    catch (const std::system_error& e)
    {
        std::cerr << e.what() << '\n';
    }
}