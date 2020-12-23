#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <memory>

#include "message.h"
#include "vector2.h"

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
    struct Serializeable//automaticly gets serialized
    {
        int textureID;
    }serializeable;

public:
    Transform transform;//Transform is also serialized

protected://functions
    virtual void serialize_(Message&);

public:
    Entity() = default;

    virtual void serialize(Message&);
    Entity(Message&);//desarialize constructor

    static std::unique_ptr<Entity> deserialize(Message);
};

#endif