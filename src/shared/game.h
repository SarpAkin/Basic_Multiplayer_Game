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
    virtual void R_EntitySpawned(Message m,int ClientID);
    Message S_EntitySpawned(int entityID,Entity& entity);

    virtual void R_EntityMoved(Message m,int ClientID);
    Message S_EntityMoved(int entityID,Entity& entity);

    void R_Ping(Message m,int ClientID);
    Message S_Ping();


public:
    void ProcessMessage(Message message,int ClientID);
    virtual void ProcessCustomMessage(Message Message,int ClientID);

};

#endif