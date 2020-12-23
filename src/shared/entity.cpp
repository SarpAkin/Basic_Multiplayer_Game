#include "entity.h"

void Entity::serialize_(Message& m)
{
    m.push_back(serializeable);
    m.push_back(transform);
}

void Entity::serialize(Message& m)
{
    m.push_back_(EntityTypes::base);
    serialize_(m);
}

Entity::Entity(Message& m)
{
    serializeable = m.pop_front<Serializeable>();
    transform = m.pop_front<Transform>();
}

std::unique_ptr<Entity> Entity::deserialize(Message m)
{
    auto etype = m.pop_front<EntityTypes>();

    switch (etype)
    {
    case EntityTypes::base:
        return std::make_unique<Entity>(m);
        break;

    default:
        return std::make_unique<Entity>(nullptr);
        break;
    }
}