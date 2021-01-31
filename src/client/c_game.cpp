#include "c_game.h"


#include "../shared/message_types.h"
#include "../shared/EntityComponents/TestComponent.h"
#include "../shared/PhysicEngine.h"

std::map<std::string,std::function<void(C_game&,std::vector<std::string>)>> C_game::commands;

C_game::C_game(uint16_t pNum, const char* ip)
    : client(pNum, ip), renderer(this)
{
    isRunning = true;
    workerThread = std::thread(
        [this]()
        {
            OnGameStart();
            if (renderer.Construct(1024, 800, 1, 1))
            {
                renderer.Start();
                std::cout << "started game\n";
            }

        }
    );
    consoleThread = std::thread(&C_game::ProcessCommands,this);
}

//it only works for strings sized 1
std::vector<std::string> splitString(std::string& s,const char* splitchar)
{
    std::size_t splitpoint = s.find(splitchar);
    std::size_t oldpoint = -1;
    std::vector<std::string> splitVec;
    while (splitpoint != std::string::npos)
    {
        splitVec.push_back(std::string(s.begin() + oldpoint + 1,s.begin() + splitpoint));
        oldpoint = splitpoint;
        splitpoint = s.find(splitchar,splitpoint);
    }
    return splitVec;
}

void C_game::ProcessCommands()
{
    std::cout << isRunning << "aaaaaaaaaaaaaaaaaabb\n";
    while (isRunning)
    {
        std::string commandRaw;
        std::cout << "aaaaaaaaaaaaaaaaaa\n";
        std::cin >> commandRaw;

        std::vector<std::string> splited = splitString(commandRaw," ");
        for(auto& sp : splited)
            std::cout << sp << '\n';
        if (splited.size())
        {
            try
            {
                commands[splited[0]](*this, std::move(splited));
            }
            catch (const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
        }
    }
}

void C_game::tick(float deltaT)
{
    //Read messages and sync with the server

    auto messages = client.connection->inqueue.GetDeque();
    for (auto& m : messages)
    {
        ProcessMessage(std::move(m), 0);
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
            simulatePhysics(Entities, deltaT, player);

            //std::cout << player.transform.velocity.ToString() << '\n';
            //client.connection->Send(S_EntityMoved(playerEntityID, player));
        }
    }
    //

    //Write messages and sync with Server
    std::vector<Message> Messages;
    SyncEntity(Messages);
    client.connection->Send(Messages);
    //
}

void C_game::OnGameStart()
{
    clientID = client.ClientID;
    auto entity = std::make_unique<Entity>();
    entity->transform.isServerSide = false;
    entity->transform.collider.size = Vector2(2, 2);
    entity->transform.drag = 0.4f;
    entity->transform.setMass(2);
    entity->didMove = true;
    entity->getComponent<TestComponent>();
    client.getConnection().Send(S_RequestEntitySpawn(std::move(entity),
        [this](Entity& e, int entityID)
        {
            setPlayer(entityID);
            //e.transform.collider.cord.x += 5;
        }));
}

void C_game::MovePlayer(Entity& player)
{
    if (renderer.GetKey(olc::Key::A).bHeld)
    {
        player.transform.staticForces.x = -speed;
    }
    else if (renderer.GetKey(olc::Key::D).bHeld)
    {
        player.transform.staticForces.x = speed;
    }
    else
    {
        player.transform.staticForces.x = 0;
    }

    if (renderer.GetKey(olc::Key::W).bHeld)
    {
        player.transform.staticForces.y = -speed;
    }
    else if (renderer.GetKey(olc::Key::S).bHeld)
    {
        player.transform.staticForces.y = speed;
    }
    else
    {
        player.transform.staticForces.y = 0;
    }
}

void C_game::stop() // Stops the game engie
{
    if (isStopped)
        return;
    isStopped = true;
    isRunning = false;
    workerThread.join();
    consoleThread.detach();
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
        }
    }
    else
    {
        std::cout << "No function!\n";
    }
}

void C_game::R_EntityUpdate(Message m, int ClientID)
{
    int entityID = m.pop_front<int>();
    auto e = findEntity(entityID);
    if (entityID == playerEntityID)
    {
        //preserve position
        Vector2 pos = e->transform.collider.cord;
        e->Deserialize(m);
        e->transform.collider.cord = pos;
    }
    else
    {
        e->Deserialize(m);
    }
}