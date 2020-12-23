#ifndef GAME
#define GAME

#include <vector>
#include <memory>
#include <map>

#include "message.h"
#include "entity.h"

enum class Gametype {
    server, client
};

class Game
{
private:
    Gametype type_;
    std::map<int,std::unique_ptr<Entity>> Entities;

private://functions


    //message Handling
    void R_EntitySpawned();
    Message S_EntitySpawned(int entityID,Entity& entity);

    void R_EntityMoved();
    Message S_EntityMoved(int entityID,Entity& entity);

public:
    void ProcessMessage(Message message);

};

#endif