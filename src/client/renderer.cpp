#include "renderer.h"

#include <vector>

#include "c_game.h"

Renderer::Renderer(C_game* game_)
{
    game = game_;
    sAppName = "Basic Multiplayer Game v0.0.1";
}

bool Renderer::OnUserUpdate(float fElapsedTime)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    
    //Set camera cord to the follow entity if it exists.
    {
        auto it = game->Entities.find(EntityToFollowID);
        if (it != game->Entities.end())
        {
            CameraCord = it->second->transform.collider.cord;
        }
    }

    //Render
    Clear(olc::DARK_BLUE);//Clear Screen
    //
    for (auto& p : game->Entities)
    {
        auto& ent = *p.second;
        DrawRect(LocalCordToScreen(ent.transform.collider.cord), olc::vi2d(1, 1), olc::WHITE);
    }
    //
    game->tick(fElapsedTime);
    return true;
}

bool Renderer::OnUserCreate()
{
    pivot = Vector2(ScreenWidth(), ScreenHeight()) / 2;
    return true;
}