#include "c_game.h"

int main()
{
    try
    {
        C_game game(30020, "127.0.0.1");
        game.stop();
        //std::cin.get();
    }
    catch (const boost::system::error_code e)
    {
        std::cerr << e.message() << '\n';
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }


    return 0;
}