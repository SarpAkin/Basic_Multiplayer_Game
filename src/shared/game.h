#ifndef GAME_H
#define GAME_H

#include <vector>
#include <memory>
#include <map>

#include "vectorBinarySearch.h"
#include "message_types.h"
#include "message.h"
#include "entity.h"

class Renderer;
//Base Game class of game engine iplementation
class Game
{
    friend Renderer;
protected:
    std::vector<std::pair<int, std::shared_ptr<Entity>>> Entities;

protected://functions

    void SyncEntity(std::vector<Message>& MToAll);

    //message Handling
    virtual void R_EntitySpawned(Message m, int ClientID);
    Message S_EntitySpawned(int entityID, Entity& entity);

    virtual void R_EntityMoved(Message m, int ClientID);
    Message S_EntityMoved(int entityID, Entity& entity);

    void R_Ping(Message m, int ClientID);
    Message S_Ping();

    virtual void R_EntityUpdate(Message m, int ClientID);
    bool S_EntityUpdate(Message& m,int entityID, Entity& entity);


public:
    void ProcessMessage(Message message, int ClientID);
    virtual void ProcessCustomMessage(Message Message, int ClientID, MessageTypes mt);

    inline std::shared_ptr<Entity> findEntity(int id)
    {
        if (auto* e = findIndVec(Entities, id))
        {
            return *e;
        }
        return std::shared_ptr<Entity>(nullptr);
    }
};

#endif