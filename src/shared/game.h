#ifndef GAME
#define GAME

#include <vector>
#include <memory>

#include "entity.h"

enum class Gametype {
    server, client
};

class Game
{
private:
    Gametype type_;
    std::vector<std::unique_ptr<Entity>> Entities;

public:
    void ProcessMessage(std::vector<char> message);
};

#endif