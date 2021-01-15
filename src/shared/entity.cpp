#include "entity.h"

#include <functional>


void Entity::serialize(Message& m)
{
    m.push_back(transform);
}

Entity::Entity(Message& m)
{
    transform = m.pop_front<Transform>();
}

std::unique_ptr<Entity> Entity::deserialize(Message m)
{
    return std::make_unique<Entity>(m);
}