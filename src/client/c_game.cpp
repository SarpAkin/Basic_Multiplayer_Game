#include "c_game.h"

C_game::C_game(uint16_t pNum, const char* ip)
    : client(pNum, ip), renderer(this)
{
    workerThread.join();
    workerThread = std::thread(
        [this]()
        {
            OnGameStart();
            if (renderer.Construct(256, 240, 4, 4))
            {
                renderer.Start();
                std::cout << "started game\n";
            }

        }
    );
}

void C_game::tick(float ElapsedTime)
{
    //Read messages and sync with the server
    auto messages = client.connection->inqueue.GetDeque();
    if (messages.size() > 0)
    {
        std::cout << messages.size() << '\n';
    }
    for (auto& m : messages)
    {

        ProcessMessage(std::move(m));
    }
    //

    //Run the Game logic
    //Such as Physic engine and Events


    //

    //Write messages and sync with Server


    //
}

void C_game::OnGameStart()
{

}

void C_game::stop() // Stops the game engie
{
    if (isStopped)
        return;
    isStopped = true;
    isRunning = false;
    workerThread.join();
    client.Stop();
}

C_game::~C_game()
{
    stop();
}