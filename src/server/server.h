#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <atomic>
#include <mutex>

#include "../shared/connection.h"

namespace asio = boost::asio;

struct Client
{
    int id;
    std::shared_ptr<Connection> connection;
};

class Server
{
private:
    asio::io_context ic;
    std::vector<Client> clients;
    std::mutex clientV_mut;
    uint32_t clCounter = 0;
    std::thread ic_thread;
    asio::ip::tcp::acceptor connection_acceptor;
public:
    T_queue<Client> NewClients;
public://fucntions
    Server(uint16_t portNum);
    ~Server();

    void Stop();
    void AddConnection(Client client);
    void AcceptConnections();
    bool VerifyConnection(asio::ip::tcp::socket& scoket_);//TODO create a blocking verify connection function

    bool SendMessage(Message, int clientId);
    bool SendMessageAll(Message mVec);
    bool SendMessageAll(Message, int clientId);

    Client GetClient(int clientID);

};

#endif