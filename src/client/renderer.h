#ifndef RENDERER_H
#define RENDERER_H

#include "../../vendor/olcPixelGameEngine.h"


class C_game;

class Renderer : public olc::PixelGameEngine
{
private:
    C_game* game;
public:
    Renderer(C_game* game_);

    bool OnUserUpdate(float fElapsedTime) override;
};

#endif