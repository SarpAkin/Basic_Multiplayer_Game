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
    //Message queue which being send to all players at the end of the frame
    std::vector<Message> MToAll;

protected:

    int SpawnEntity(std::unique_ptr<Entity>);

    void SendMessageAll(Message m,int exceptPlayer = -1);
    //events
    void OnGameStart();
    void OnPlayerJoin(Client player);//Called When a player joins 

    //Messages
    void ProcessCustomMessage(Message Message, int ClientID) override;

    void R_RequestEntitySpawn(Message, int);
    void R_PlayerJoined(Message, int);

    Message S_ReplyEntityRequest(int ReplyID,int entityID);
    //Message Overrides
    void R_EntitySpawned(Message m, int ClientID) override;
    void R_EntityMoved(Message m, int ClientID) override;

    //inlines
    inline std::shared_ptr<Connection> findPlayer(int id)
    {
        for(auto& p : players)
        {
            if(p.id == id)
            {
                return p.connection;
            }
        }
        return std::shared_ptr<Connection>(nullptr);
    }
public:

    ~S_game();

    void start(uint16_t portNum, bool tickAutomaticly = true);
    void stop();

    void tick(double ElapsedTime);
};


#endif