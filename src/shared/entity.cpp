#include "entity.h"

#include <functional>


void Entity::serialize(Message& m)
{
    m.push_back(transform);
    //do it last
    //Compenent::SerializeAll(c,m);

}

Entity::Entity(Message& m)
{
    transform = m.pop_front<Transform>();

    //last
    Compenent::DeserializeAll(this,m);
}

std::unique_ptr<Entity> Entity::deserialize(Message m)
{
    return std::make_unique<Entity>(m);
}