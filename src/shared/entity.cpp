#include "entity.h"

#include <functional>


bool Entity::serialize(Message& m)
{
    m.push_back(didMove);
    size_t size = m.size();
    if(didMove)
        m.push_back(transform);
    //do it last
    //Component::SerializeAll(components,m);
    //return false if nothing is serialized
    return m.size() > size;
}

void Entity::Deserialize(Message& m)
{
    if(m.pop_front<bool>())
        transform = m.pop_front<Transform>();
    //do it last
    //Component::DeserializeAll(this,m);

}

Entity::Entity(Message& m)
{
    Deserialize(m);
    std::cout << transform.collider.cord.ToString() << std::endl;
}

std::unique_ptr<Entity> Entity::deserialize(Message m)
{
    return std::make_unique<Entity>(m);
}