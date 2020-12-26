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

    int EntityToFollowID = -1;
    Vector2 CameraCord;
    Vector2 pivot;
    float TileSize = 32.0f;
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
    inline olc::vi2d LocalCordToScreen(Vector2 v)
    {
        Vector2 final = (v - GetCamCord()) * TileSize;
        return olc::vi2d((int32_t)final.x, (int32_t)final.y);
    }
};

#endif