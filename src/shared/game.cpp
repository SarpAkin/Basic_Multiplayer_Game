#include "game.h"
#include "message_types.h"




//Message handling

void Game::ProcessMessage(Message message, int ClientID)
{
    MessageTypes mtype = message.pop_front<MessageTypes>();

    switch (mtype)
    {
    case MessageTypes::EntitySpwaned:
        R_EntitySpawned(std::move(message), ClientID);
        break;
    case MessageTypes::EntityMoved:
        R_EntityMoved(std::move(message), ClientID);
        break;
    case MessageTypes::Ping:
        R_Ping(std::move(message), ClientID);
        break;
    default:
        std::cout << "processing custom message\n";
        ProcessCustomMessage(std::move(message), ClientID, mtype);
        break;
    }
}

void Game::ProcessCustomMessage(Message message, int ClientID, MessageTypes mt)
{
    std::cout << "Not overrided\n";
}


void Game::R_EntitySpawned(Message m, int ClientID)
{
    //std::cout << "Receveid message spawning entity!\n";
    //std::cout << "Message size: " << m.data.size() << '\n';
    int entityID = m.pop_front<int>();
    //std::cout << "Entity id: " << entityID << '\n';
    auto e = Entity::deserialize(std::move(m));
    Entities.insert(std::pair<int, std::unique_ptr<Entity>>(entityID, std::move(e)));
}

Message Game::S_EntitySpawned(int entityID, Entity& entity)
{
    Message m;
    m.push_back_(MessageTypes::EntitySpwaned);
    m.push_back(entityID);
    entity.serialize(m);
    /*
    std::cout << "Sending message spawning entity!\n";
    std::cout << "Message size: " << m.data.size() << '\n';
    std::cout << "Entity id: " << entityID << '\n';
    */
    return std::move(m);
}

void Game::R_EntityMoved(Message m, int ClientID)
{
    int EntityID = m.pop_front<int>();
    auto transform = m.pop_front<Transform>();
    auto e = Entities.find(EntityID);
    e->second->transform = transform;
}

Message Game::S_EntityMoved(int entityID, Entity& entity)
{
    Message m;
    m.push_back_(MessageTypes::EntityMoved);
    m.push_back(entityID);
    m.push_back(entity.transform);
    return std::move(m);
}

void Game::R_Ping(Message m, int ClientID)
{
    std::cout << "Got Pinged\n";

}

Message Game::S_Ping()
{
    std::cout << "Pinging\n";
    Message m;
    m.push_back_(MessageTypes::Ping);
    return std::move(m);
}
