#ifndef C_GAME_H
#define C_GAME_H

#include <functional>
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

    int EntityRequestCounter = 0;
    //Lambda functions which are stored for later execution when the EntityRequest Repiled.
    std::map<int,std::function<void(Entity&,int)>> EntityRequestFunctions;
public:
    int clientID;

protected://functions
    void OnGameStart();
    
    void MovePlayer(Entity& player);
    //Don't uncomment unitl define it
    //void ProcessCustomMessage(Message Message, int ClientID) override; 

    //Messages
    void ProcessCustomMessage(Message m, int ClientID) override;

    Message S_RequestEntitySpawn(std::unique_ptr<Entity>,std::function<void(Entity&,int)>);
    Message S_PlayerJoined(int);

    void R_ReplyEntityRequest(Message m);
public:
    C_game(uint16_t, const char*);
    ~C_game();

    void stop();

    void tick(float ElapsedTime);
};

//cpp part 
//TODO move to a cpp file

#endif
