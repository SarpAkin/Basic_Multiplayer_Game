#include "server.h"

#include "../shared/welcomeMessage.h"

Server::Server(uint16_t portNum)
    : connection_acceptor(ic, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), portNum))
{
    std::cout << "Server Started\n";
    AcceptConnections();
    ic_thread = std::thread([this]() {
        try
        {
            ic.run();
        }
        catch (const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        });
}

void Server::AddConnection(Client cl)
{
    NewClients.push_back(cl);

    clientV_mut.lock();
    clients.push_back(std::move(cl));
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
                int cnum = ++clCounter;

                welcomeMessage mes;
                mes.ClientID = cnum;
                _socket.write_some(asio::buffer(&mes,sizeof(welcomeMessage)));

                client.id = cnum;
                client.connection = std::make_shared<Connection>(std::move(_socket), ic);
                AddConnection(std::move(client));
            }
            else
            {
                //TODO handle error
                std::cout << ec.message() << std::endl;
            }
        });
}

bool Server::VerifyConnection(asio::ip::tcp::socket& socket_)
{
    MHeader header;
    try
    {
        socket_.wait(socket_.wait_read);
        socket_.read_some(asio::buffer(&header, sizeof(MHeader)));
    }
    catch (const boost::system::error_code e)
    {
        std::cerr << e.message() << '\n';
        return false;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
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
    clients.clear();
    std::cout << "Server Stopped\n";
}

Server::~Server()
{
    Stop();
}

bool Server::SendMessage(Message mVec, int clientId)
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

bool Server::SendMessageAll(Message mVec)
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

bool Server::SendMessageAll(Message mVec, int clientId)
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

Client Server::GetClient(int clientID)
{
    clientV_mut.lock();

    for (auto& cl : clients)
    {
        if (cl.id == clientID)
        {
            if (cl.connection->isopen())
            {
                auto tmp = cl;
                clientV_mut.unlock();
                return tmp;
            }
        }
    }

    clientV_mut.unlock();
    return Client();
}