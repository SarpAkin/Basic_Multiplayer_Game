#include "game.h"
#include "message_types.h"




//Message handling

void Game::ProcessMessage(Message message, int ClientID)
{
    //std::cout << "Message size " << message.size() << '\n';
    MessageTypes mtype = message.pop_front<MessageTypes>();
    //std::cout << "Message Type " << (int)mtype << '\n';
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
    case MessageTypes::EntityUpdate:
        R_EntityUpdate(std::move(message), ClientID);
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
    std::cout  << "Receveid message spawning entity!\n";
    //std::cout << "Message size: " << m.size() << '\n';
    int entityID = m.pop_front<int>();
    //std::cout << "Entity id: " << entityID << '\n';
    auto e = Entity::deserialize(std::move(m));
    std::cout << e->transform.collider.size.ToString() << '\n';
    Entities.emplace_back(entityID, std::move(e));
}

Message Game::S_EntitySpawned(int entityID, Entity& entity)
{
    Message m;
    m.push_back_(MessageTypes::EntitySpwaned);
    m.push_back(entityID);
    entity.didMove = true;
    entity.serialize(m);
    entity.didMove = false;
    /*std::map<int,std::unique_ptr<Entity>> Entities_;
    std::cout << "Sending message spawning entity!\n";
    std::cout << "Message size: " << m.size() << '\n';
    std::cout << "Entity id: " << entityID << '\n';
    */
    return m;
}
void Game::R_EntityMoved(Message m, int ClientID) 
{
    int EntityID = m.pop_front<int>();
    auto transform = m.pop_front<Transform>();
    auto e = findEntity(EntityID);
    e->transform = transform;
}

Message Game::S_EntityMoved(int entityID, Entity& entity)
{
    //std::cout << "MOved\n";
    Message m;
    m.push_back_(MessageTypes::EntityMoved);
    m.push_back(entityID);
    m.push_back(entity.transform);
    return m;
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
    return m;
}

void Game::R_EntityUpdate(Message m, int ClientID)//there is an override at c_game.cpp
{
    int entityID = m.pop_front<int>();
    findEntity(entityID)->Deserialize(m);
}

bool Game::S_EntityUpdate(Message& m, int entityID, Entity& entity)
{
    m.push_back_(MessageTypes::EntityUpdate);
    m.push_back(entityID);
    return entity.serialize(m);
}

void Game::SyncEntity(std::vector<Message>& mVec)
{
    mVec.reserve(mVec.size() + Entities.size());
    for (auto& e : Entities)
    {
        Message m;
        if (S_EntityUpdate(m, e.first, *e.second))
            mVec.push_back(m);
    }
}