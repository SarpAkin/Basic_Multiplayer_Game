#include "client.h"


Client::Client(uint16_t portNum, const char* ip)
{
    auto endpoint = asio::ip::tcp::endpoint(asio::ip::make_address(ip), portNum);
    asio::ip::tcp::socket socket_(ic);
    socket_.connect(endpoint);
    MHeader header;
    header.DataSize = 0;
    socket_.write_some(asio::buffer(&header,sizeof(header)));
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
        connection->Stop();
        ic.stop();
        ic_thread.join();
    }
}

Client::~Client()
{
    Stop();
}