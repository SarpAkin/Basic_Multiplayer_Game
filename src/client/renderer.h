#ifndef RENDERER_H
#define RENDERER_H

#include <memory>

#include "../../vendor/olcPixelGameEngine.h"//

#include "../shared/vector2.h"
#include "../shared/entity.h"

class C_game;

class Renderer : public olc::PixelGameEngine
{
private:
    C_game* game;

    Vector2 CameraCord;
    Vector2 pivot;
    float TileSize = 12.0f;
public:
    int EntityToFollowID = -1;
public:
    Renderer(C_game* game_);

    void RenderEntity(Entity&);

    bool OnUserUpdate(float fElapsedTime) override;
    bool OnUserCreate() override;

    //inlines
    inline Vector2 GetCamCord()
    {
        return CameraCord - pivot / TileSize;
    }
    inline Vector2 ScreenCordToLocal(int x, int y)
    {
        return GetCamCord() + Vector2(x, y) / TileSize;
    }
    inline olc::vf2d LocalCordToScreen(Vector2 v)
    {
        return (v - GetCamCord()) * TileSize;
    }
};

#endif