 #include "c_game.h"

int main()
{
    C_game game(30020,"127.0.0.1");
    game.stop();
    std::cin.get();
    return 0;
}