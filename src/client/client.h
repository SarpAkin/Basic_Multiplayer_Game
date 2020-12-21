#ifndef CLIENT
#define CLIENT

#include <memory>

#include "../shared/connection.h"

class Client
{
private:
    asio::io_context ic;
    std::thread ic_thread;
    std::unique_ptr<Connection> connection;

    bool isRunning = true;
public:
    void Stop();

    Client(uint16_t portNum, const char* ip);
    ~Client();

    //inlines
    inline Connection& getConnection()
    {
        return *connection;
    }
};

Client::Client(uint16_t portNum, const char* ip)
{
    auto endpoint = asio::ip::tcp::endpoint(asio::ip::make_address(ip), portNum);
    asio::ip::tcp::socket socket_(ic);
    socket_.connect(endpoint);
    connection = std::make_unique<Connection>(std::move(socket_), ic);

    ic_thread = std::thread(
        [this]()
        {
            ic.run();
        });
}

void Client::Stop()
{
    if (isRunning)
    {
        isRunning = false;
        ic.stop();
        connection->Stop();
        ic_thread.join();
    }
}

Client::~Client()
{
    Stop();
}


#endif