#include "game.h"
#include "message_types.h"




//Message handling

void Game::ProcessMessage(Message message)
{
    MessageTypes mtype = message.pop_front<MessageTypes>();

    switch (mtype)
    {
    case MessageTypes::EntitySpwaned :
        R_EntitySpawned(std::move(message));
        break;
    
    default:
        break;
    }
}


void Game::R_EntitySpawned(Message m)
{
    int entityID = m.pop_front<int>();
    auto e = Entity::deserialize(std::move(m));

    Entities.insert(std::pair<int, std::unique_ptr<Entity>>(entityID, std::move(e)));
}

Message Game::S_EntitySpawned(int entityID, Entity& entity)
{
    Message m;
    m.push_back_(MessageTypes::EntitySpwaned);
    m.push_back(entityID);
    entity.serialize(m);
    return std::move(m);
}
