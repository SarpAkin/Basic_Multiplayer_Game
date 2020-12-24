#ifndef GAME_H
#define GAME_H

#include <vector>
#include <memory>
#include <map>

#include "message.h"
#include "entity.h"


//Base Game class of game engine iplementation
class Game
{
public:
    std::map<int,std::unique_ptr<Entity>> Entities;

protected://functions


    //message Handling
    void R_EntitySpawned(Message m);
    Message S_EntitySpawned(int entityID,Entity& entity);

    void R_EntityMoved(Message m);
    Message S_EntityMoved(int entityID,Entity& entity);

    void R_Ping(Message m);
    Message S_Ping();


public:
    void ProcessMessage(Message message);

};

#endif