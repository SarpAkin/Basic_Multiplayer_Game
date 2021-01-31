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
    int playerEntityID = -1;

    std::thread workerThread;
    std::thread consoleThread;
    bool isRunning = true;
    bool isStopped = false;

    int EntityRequestCounter = 0;
    //Lambda functions which are stored for later execution when the EntityRequest Repiled.
    std::map<int, std::function<void(Entity&, int)>> EntityRequestFunctions;
public:
    float speed = 8;
    int clientID;

    static std::map<std::string,std::function<void(C_game&,std::vector<std::string>)>> commands;
private://functions
    void ProcessCommands();
protected:
    void OnGameStart();

    void MovePlayer(Entity& player);
    //Don't uncomment unitl define it
    //void ProcessCustomMessage(Message Message, int ClientID) override; 

    //Messages
    void ProcessCustomMessage(Message m, int ClientID, MessageTypes mt) override;
    void R_EntityUpdate(Message m, int ClientID) override;

    Message S_RequestEntitySpawn(std::unique_ptr<Entity>, std::function<void(Entity&, int)>);
    Message S_PlayerJoined(int);

    void R_ReplyEntityRequest(Message m);

    //inilnes
    inline void setPlayer(int id)
    {
        playerEntityID = id;
        renderer.EntityToFollowID = id;
    }
public:
    C_game(uint16_t, const char*);
    ~C_game();

    void stop();

    void tick(float ElapsedTime);
};

//cpp part 
//TODO move to a cpp file

#endif
