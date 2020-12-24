#ifndef C_GAME_H
#define C_GAME_H

#include <thread>
#include <memory>
#include <vector>

#include "renderer.h"
#include "client.h"

#include "../shared/game.h"

//Client Side of the game
class C_game : public Game
{
private:
    Client client;//Connection to the server
    Renderer renderer;

    //Creates an empty thread to make it joinable
    std::thread workerThread = std::thread(([]() {/*do nothing*/}));

    bool isRunning = true;
    bool isStopped = false;

protected://functions
    void OnGameStart();
public:
    C_game(uint16_t, const char*);
    ~C_game();

    void stop();

    void tick(float ElapsedTime);
};

//cpp part 
//TODO move to a cpp file

C_game::C_game(uint16_t pNum, const char* ip)
    : client(pNum, ip), renderer(this)
{
    workerThread.join();
    workerThread = std::thread(
        [this]()
        {
            OnGameStart();
            if(renderer.Construct(256, 240, 4, 4))
            {
                renderer.Start();
            }
            
        }
    );
}

void C_game::tick(float ElapsedTime)
{
    //Read messages and sync with the server
    auto messages =  client.connection->inqueue.GetDeque();
    for(auto& m : messages)
    {
        ProcessMessage(std::move(m));
    }
    //

    //Run the Game logic
    //Such as Physic engine and Events


    //

    //Write messages and sync with Server


    //
}

void C_game::stop() // Stops the game engie
{
    if(isStopped)
        return;
    isRunning = false;
    workerThread.join();
}

C_game::~C_game()
{
    stop();
}

#endif
