#include "server.h"

Server::Server(uint16_t portNum)
    : connection_acceptor(ic, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), portNum))
{
    std::cout << "Server Started\n";
    AcceptConnections();
    ic_thread = std::thread([this]() {
        ic.run();
        });
}

void Server::AddConnection(Client cl)
{
    clientV_mut.lock();
    clients.push_back(std::move(cl));
    std::string str = "Succesfully Connected To server " + std::to_string(clients.back().id);
    std::vector<char> dVec(str.begin(), str.end());
    clients.back().connection.get()->Send(std::move(dVec));
    clientV_mut.unlock();
}

void Server::AcceptConnections()
{
    connection_acceptor.async_accept([this](boost::system::error_code ec, asio::ip::tcp::socket _socket)
        {
            AcceptConnections();
            if (!ec)
            {
                if (!VerifyConnection(_socket))//Blocking method for verifying connection.
                    return;
                std::cout << "Adding Connection to server!" << std::endl;
                Client client;
                int cnum = clCounter;
                clCounter++;
                client.id = cnum;
                client.connection = std::make_unique<Connection>(std::move(_socket), ic);
                AddConnection(std::move(client));
            }
            else
            {
                //TODO handle error
                std::cout << ec.message() << std::endl;
            }
        });
}

bool Server::VerifyConnection(asio::ip::tcp::socket& scoket_)
{
    //TODO
    return true;
}

void Server::Stop()
{
    connection_acceptor.cancel();
    connection_acceptor.close();
    clientV_mut.lock();
    for (auto& cl : clients)
    {
        cl.connection->Stop();
    }
    clientV_mut.unlock();
    ic.stop();
    ic_thread.join();
    std::cout << "Server Stopped\n";
}

Server::~Server()
{
    Stop();
}

bool Server::SendMessage(std::vector<char> mVec, int clientId)
{
    clientV_mut.lock();

    for (auto& cl : clients)
    {
        if (cl.id == clientId)
        {
            if (cl.connection->isopen())
            {
                cl.connection->Send(std::move(mVec));
                clientV_mut.unlock();//Unlock it on return
                return true;
            }
        }
    }

    clientV_mut.unlock();
    return false;
}

bool Server::SendMessageAll(std::vector<char> mVec)
{
    clientV_mut.lock();

    std::cout << clients.size() << '\n';
    for (auto& cl : clients)
    {
        if (cl.connection->isopen())
        {
            auto mCopy = mVec;
            cl.connection->Send(std::move(mCopy));
        }
    }

    clientV_mut.unlock();
    return true;
}

bool Server::SendMessageAll(std::vector<char> mVec, int clientId)
{
    clientV_mut.lock();

    std::cout << clients.size() << '\n';
    for (auto& cl : clients)
    {
        if (cl.id != clientId)
        {
            if (cl.connection->isopen())
            {
                auto mCopy = mVec;
                cl.connection->Send(std::move(mCopy));
            }
        }
    }

    clientV_mut.unlock();
    return true;
}

