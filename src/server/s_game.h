#ifndef S_GAME_H
#define S_GAME_H

#include <thread>
#include <memory>
#include <vector>

#include "../shared/game.h"
#include "server.h"

//Server Side of the game
class S_game : public Game
{
private:
    int EntityCounter = 0;

    bool isStopped = false;
    bool isStarted = false;
    bool isRunning = true;

    //Creates an empty thread to make it joinable
    std::thread workerThread = std::thread(([]() {/*do nothing*/}));

    std::unique_ptr<Server> server;
    std::vector<Client> players;

protected:

    void SpawnEntity(std::unique_ptr<Entity>);
    //events
    void OnGameStart();
    void OnPlayerJoin(Client player);//Called When a player joins 
public:

    ~S_game();

    void start(uint16_t portNum, bool tickAutomaticly = true);
    void stop();

    void tick(double ElapsedTime);
};

//cpp part 
//TODO move to a cpp file

#include <chrono>

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

                    //std::this_thread::sleep_for(std::chrono::milliseconds(10));

                    tick(deltaTime);

                    ++CounterT;
                    if (CounterF >= 1)
                    {
                        CounterF -= 1.0f;
                        std::cout << "Frames rendered " << CounterT << '\n';
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
    isRunning = false;
    workerThread.join();
    server->Stop();
}

void S_game::tick(double ElapsedTime)
{
    //Read messages and sync the server


    //

    //Run the Game logic
    //Such as Physic engine and Events


    //

    //Write messages and sync with players


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
    SpawnEntity(std::make_unique<Entity>());
}

void S_game::OnPlayerJoin(Client player)
{
    //std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout <<Entities.size() << "Syncinc the new player!\n";
    std::vector<Message> ms;
    ms.reserve(Entities.size());
    for (auto& e : Entities)
    {
        ms.push_back(S_EntitySpawned(e.first, *e.second));
    }
    player.connection->Send(S_Ping());
    player.connection->Send(std::move(ms));
}

void S_game::SpawnEntity(std::unique_ptr<Entity> e)
{
    int id = EntityCounter++;
    S_EntitySpawned(id, *e);//unfinihed
    Entities.emplace(id, std::move(e));
}

S_game::~S_game()
{
    stop();
}

#endif