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
    bool isStarted = false;
    bool isRunning = true;

    std::thread workerThread = std::thread(([](){/*do nothing*/})); //Creates an empty thread to make it joinable.
    std::unique_ptr<Server> server;
    std::vector<Client> players;

protected:

    //events
    void OnPlayerJoin(Client player);//Called When a player joins 
public:

    void start(uint16_t portNum, bool tickAutomaticly = true);
    void stop();

    void tick(float ElapsedTime);
};

//cpp part 
//TODO move to a cpp file

void S_game::start(uint16_t portNum, bool tickAutomaticly = true)
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
                while (isRunning)
                {
                    //TODO Measure last frames duration and input to the next tick call
                    tick(0.0f);
                }
                
            }
        );
    }
}

void S_game::stop() // Stops the game engie
{
    isRunning = false;
    workerThread.join();
    server->Stop();
}

void S_game::tick(float ElapsedTime)
{
    //Read messages and sync the server

    //

    //Run the Game logic
    //Such as Physic engine and Events

    //

    //Write messages and sync with players

    // 
}

#endif