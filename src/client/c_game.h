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

#endif
