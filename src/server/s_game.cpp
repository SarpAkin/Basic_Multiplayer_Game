#include "s_game.h"

#include <chrono>

#include "../shared/message_types.h"

void S_game::start(uint16_t portNum, bool tickAutomaticly)
{
    if (isStarted)//Return if it is already started
        return;
    server = std::make_unique<Server>(portNum);
    if (tickAutomaticly)
    {
        workerThread.join();
        workerThread = std::thread(
            [this]()
            {
                OnGameStart();
                double deltaTime = 0.001f;
                double CounterF = 0;
                int CounterT = 0;
                auto s = std::chrono::steady_clock::now();
                while (isRunning)
                {
                    auto e = s;
                    s = std::chrono::steady_clock::now();

                    auto dur = s - e;
                    deltaTime = dur.count();
                    deltaTime /= 1000000000;
                    CounterF += deltaTime;


                    tick(deltaTime);

                    ++CounterT;
                    if (CounterF >= 1)
                    {
                        CounterF -= 1.0f;
                        //std::cout << "Frames rendered " << CounterT << '\n';
                        CounterT = 0;

                        /*for (auto& p : players)
                        {
                            p.connection->Send(S_Ping());
                        }*/
                    }
                }
            }
        );
    }
}

void S_game::stop() // Stops the game engie
{
    if (isStopped)
        return;
    isStopped = true;
    isRunning = false;
    workerThread.join();
    players.clear();
    server = nullptr;
    std::cout << "Stopped server\n";
}

void S_game::tick(double ElapsedTime)
{
    //Read messages and sync the server
    for (auto& p : players)
    {
        auto messages = p.connection->inqueue.GetDeque();
        for (auto& m : messages)
        {
            ProcessMessage(std::move(m), p.id);
        }
    }

    //

    //Run the Game logic
    //Such as Physic engine and Events


    //

    //Write messages and sync with players
    for (int i = players.size() - 1;i >= 0;--i)
    {
        if (!players[i].connection->Send(MToAll))
        {
            //Erase the player if it fails to send message
            std::cout << "Player disconnected!\n";
            players.erase(players.begin() + i);
        }
    }

    // 

    //handle New Players

    auto newPlayers = server->NewClients.GetDeque();
    for (auto& np : newPlayers)
    {
        OnPlayerJoin(np);
        players.push_back(std::move(np));
    }

    //
}

void S_game::OnGameStart()
{

}

void S_game::OnPlayerJoin(Client player)
{
    //std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << Entities.size() << "Syncinc the new player!\n";

    player.connection->Send(S_Ping());

    std::vector<Message> ms;
    ms.reserve(Entities.size());
    for (auto& e : Entities)
    {
        ms.push_back(S_EntitySpawned(e.first, *e.second));
    }
    player.connection->Send(std::move(ms));
}

int S_game::SpawnEntity(std::unique_ptr<Entity> e)
{
    int id = EntityCounter++;
    SendMessageAll(S_EntitySpawned(id, *e));
    Entities.emplace(id, std::move(e));
    return id;
}

void S_game::SendMessageAll(Message m, int pID)
{
    //TODO erase if it returns false
    for (auto& p : players)
    {
        if (p.id != pID)
        {
            p.connection->Send(m);
        }
    }
}

S_game::~S_game()
{
    stop();
}

//Messages

void S_game::ProcessCustomMessage(Message m, int ClientID, MessageTypes mt)
{
    //MessageTypes mt = m.pop_front<MessageTypes>();
    switch (mt)
    {
    case MessageTypes::RequestEntitySpawn:
        R_RequestEntitySpawn(std::move(m), ClientID);
        break;

    case MessageTypes::PlayerJoined:
        R_PlayerJoined(std::move(m), ClientID);
        break;

    default:
        break;
    }
}

void S_game::R_RequestEntitySpawn(Message m, int ClientID)
{
    std::cout << "received\n";
    auto ReplyID = m.pop_front<int>();
    auto e = Entity::deserialize(std::move(m));
    int Eid = SpawnEntity(std::move(e));
    auto p = findPlayer(ClientID);
    if (p)
    {
        p->Send(S_ReplyEntityRequest(ReplyID, Eid));
    }
}

Message S_game::S_ReplyEntityRequest(int ReplyID, int EntityID)
{
    Message m;
    m.push_back_(MessageTypes::ReplyEntityRequest);
    m.push_back(ReplyID);
    m.push_back(EntityID);
    return std::move(m);
}

void S_game::R_PlayerJoined(Message m, int ClientID)
{

}

//Message overrides

//TODO remove this from overrides and virtuals
void S_game::R_EntitySpawned(Message m, int ClientID)
{
    int entityID = m.pop_front<int>();
    auto e = Entity::deserialize(std::move(m));

    Entities.insert(std::pair<int, std::unique_ptr<Entity>>(entityID, std::move(e)));
}

void S_game::R_EntityMoved(Message m, int ClientID)
{

    int EntityID = m.pop_front<int>();
    auto transform = m.pop_front<Transform>();
    auto e = Entities.find(EntityID);

    if (e != Entities.end())
    {
        auto entity = *(e->second);
        entity.transform = transform;

        //send to other players
        SendMessageAll(S_EntityMoved(EntityID, entity), ClientID);
    }
    //
}