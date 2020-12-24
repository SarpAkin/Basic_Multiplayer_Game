#ifndef CLIENT_h
#define CLIENT_H

#include <memory>

#include "../shared/connection.h"

class Client
{
private:
    asio::io_context ic;
    std::thread ic_thread;

    bool isRunning = true;
public:
    std::unique_ptr<Connection> connection;

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


#endif