#include "vector2.h"

#include <cmath>


Vector2::Vector2(float x,float y)
{
    this->x = x;
    this->y = y;
}

float Vector2::distance(Vector2 a,Vector2 b)
{
    return sqrtf((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}
#ifndef SERVER_SIDE
#include "../../vendor/olcPixelGameEngine.h"//
Vector2::operator olc::vf2d()
{
    return olc::vf2d(x,y);
}
#endif