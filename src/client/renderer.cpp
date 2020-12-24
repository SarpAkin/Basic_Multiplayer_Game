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
    //Render
    for(auto& p : game->Entities)
    {
        auto& ent = *p.second;
        DrawRect(0,0,1,1,olc::WHITE);
    }
    //
    game->tick(fElapsedTime);
}