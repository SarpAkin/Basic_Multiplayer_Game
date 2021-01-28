#include "c_game.h"


#include "../shared/message_types.h"
#include "../shared/EntityComponents/TestComponent.h"

C_game::C_game(uint16_t pNum, const char* ip)
    : client(pNum, ip), renderer(this)
{
    workerThread.join();
    workerThread = std::thread(
        [this]()
        {
            OnGameStart();
            if (renderer.Construct(256, 240, 4, 4))
            {
                renderer.Start();
                std::cout << "started game\n";
            }

        }
    );
}

bool tmpbool = true;

void C_game::tick(float ElapsedTime)
{
    //Read messages and sync with the server
    if (tmpbool)
    {
        auto messages = client.connection->inqueue.GetDeque();
        for (auto& m : messages)
        {
            ProcessMessage(std::move(m), 0);
        }
    }
    //

    //Run the Game logic
    //Such as Physic engine and Events

    {
        //move player
        if (auto playerit = findEntity(playerEntityID))
        {
            //tmpbool = false;
            Entity& player = *playerit;
            MovePlayer(player);
            player.transform.collider.cord +=
                player.transform.velocity * ElapsedTime;
            client.connection->Send(S_EntityMoved(playerEntityID, player));
        }
    }
    //

    //Write messages and sync with Server


    //
}

void C_game::OnGameStart()
{
    clientID = client.ClientID;
    auto entity = std::make_unique<Entity>();
    entity->transform.isServerSide = false;
    client.getConnection().Send(S_Ping());
    //entity->getComponent<TestComponent>();
    client.getConnection().Send(S_RequestEntitySpawn(std::move(entity),
        [this](Entity& e, int entityID)
        {
            //std::cout << "aaa\n";
            setPlayer(entityID);
            //e.transform.collider.cord.x += 5;
        }));
}

void C_game::MovePlayer(Entity& player)
{
    float speed = 5;
    if (renderer.GetKey(olc::Key::A).bHeld)
    {
        player.transform.velocity.x = -speed;
    }
    else if (renderer.GetKey(olc::Key::D).bHeld)
    {
        player.transform.velocity.x = speed;
    }
    else
    {
        player.transform.velocity.x = 0;
    }

    if (renderer.GetKey(olc::Key::W).bHeld)
    {
        player.transform.velocity.y = -speed;
    }
    else if (renderer.GetKey(olc::Key::S).bHeld)
    {
        player.transform.velocity.y = speed;
    }
    else
    {
        player.transform.velocity.y = 0;
    }
}

void C_game::stop() // Stops the game engie
{
    if (isStopped)
        return;
    isStopped = true;
    isRunning = false;
    workerThread.join();
    client.Stop();
}

C_game::~C_game()
{
    stop();
}

//Messages

void C_game::ProcessCustomMessage(Message m, int ClientID, MessageTypes mt)
{
    switch (mt)
    {
    case MessageTypes::ReplyEntityRequest:
        R_ReplyEntityRequest(std::move(m));
        break;

    default:
        break;
    }
}

Message C_game::S_RequestEntitySpawn(std::unique_ptr<Entity> e, std::function<void(Entity&, int)> lfunc)
{
    int replyID = EntityRequestCounter++;
    EntityRequestFunctions.emplace(replyID, lfunc);
    Message m;
    m.push_back_(MessageTypes::RequestEntitySpawn);
    m.push_back(replyID);
    e->serialize(m);
    return m;
}

Message C_game::S_PlayerJoined(int playerEntity)
{
    Message m;
    m.push_back_(MessageTypes::PlayerJoined);
    m.push_back(playerEntity);
    return m;
}

void C_game::R_ReplyEntityRequest(Message m)
{
    std::cout << "R_ReplyEntityRequest\n";
    std::cout << m.size() << '\n';
    int ReplyID = m.pop_front<int>();
    int EntityID = m.pop_front<int>();
    auto funcit = EntityRequestFunctions.find(ReplyID);
    if (funcit != EntityRequestFunctions.end())
    {
        auto func = funcit->second;
        EntityRequestFunctions.erase(funcit);

        if (auto e = findEntity(EntityID))
        {
            func(*e, EntityID);
        }
        else
        {
            std::cout << EntityID << " Entity doesn't exist. not executing the function\n";
            for (auto& e : Entities)
            {
                std::cout << e.first << ' ';
            }
            std::cout << '\n';
        }
    }
    else
    {
        std::cout << "No function!\n";
    }
}