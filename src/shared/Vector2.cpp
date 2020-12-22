#include "Vector2.h"

#include <math.h>


Vector2::Vector2(float x,float y)
{
    this->x = x;
    this->y = y;
}
Vector2::Vector2()
{
    //leave empty
}

float Vector2::distance(Vector2 a,Vector2 b)
{
    return sqrtf((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}