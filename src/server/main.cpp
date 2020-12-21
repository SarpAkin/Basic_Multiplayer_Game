#include <iostream>

#include "server.h"

int main()
{
    try
    {
        Server server(30020);
        std::cin.get();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}