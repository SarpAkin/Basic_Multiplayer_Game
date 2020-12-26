#ifndef CONNECTION_H
#define CONNECTION_H

#include <functional>
#include <iostream>
#include <vector>
#include <thread>

#include <boost/asio/ts/internet.hpp>
#include <boost/asio/ts/buffer.hpp>
#include <boost/asio.hpp>

#include "Tsafe_queue.h"
#include "message.h"

namespace asio = boost::asio;

struct MHeader
{
    uint32_t DataSize;
};

class Connection
{
private:
    std::thread WorkerThread = std::thread([]() {/*do nothing*/});
    asio::io_context* i_cont;
    asio::ip::tcp::socket socket_;
    std::function<void(Message&& dVec)> OnMessageReceive;

    bool useQueueOnMessageReceive = true;
    bool isOpen = true;

    T_queue<Message> outqueue;

    std::vector<char> readHBuffer = std::vector<char>(sizeof(MHeader));
    Message readBBuffer;

    std::vector<char> writeHBuffer = std::vector<char>(sizeof(MHeader));
    Message writeBBuffer;

public:
    T_queue<Message> inqueue;

private:
    void listen();
    void write();

public:
    Connection(asio::ip::tcp::socket&& socket__, asio::io_context& ic);
    Connection(asio::ip::tcp::socket&& socket__, std::function<void(Message&& dVec)>, asio::io_context& ic);
    ~Connection();

    void Stop();
    bool Send(Message DVec);
    bool Send(std::vector<Message> DVec);

    //inlines
    inline bool isopen()
    {
        return isOpen;
    }
};

#endif