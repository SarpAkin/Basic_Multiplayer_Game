#ifndef SERVER
#define SERVER

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
    uint32_t id;
    std::shared_ptr<Connection> connection;
};

const auto lambda = [](std::vector<char> dVec)
{
    for (char c : dVec)
    {
        std::cout << c;
    }
    std::cout << std::endl;
};

class Server
{
public:
    asio::io_context ic;
private:
    std::vector<Client> clients;
    std::mutex clientV_mut;
    uint32_t clCounter = 0;
    std::thread ic_thread;
    asio::ip::tcp::acceptor connection_acceptor;

public:
    Server(uint16_t portNum);
    ~Server();

    void Stop();
    void AddConnection(Client client);
    void AcceptConnections();
    bool VerifyConnection(asio::ip::tcp::socket& scoket_);//TODO create a blocking verify connection function

    bool SendMessage(Message, int clientId);
    bool SendMessageAll(Message mVec);
    bool SendMessageAll(Message,int clientId);

};

#endif