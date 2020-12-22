#ifndef ENTITY
#define ENTITY

#include <vector>

#include "Vector2.h"

enum class EntityTypes
{
    base
};

struct Transform
{
    AABB collider;
    Vector2 velocity;
};

class Entity//base 
{
private:

protected:

public:
    Transform transform;

public:
    Entity() = default;
    virtual std::vector<char> serialize();
    
};

#endif