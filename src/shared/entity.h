#ifndef ENTITY_H
#define ENTITY_H

#include <type_traits>
#include <vector>
#include <memory>

#include "message.h"
#include "vector2.h"

#include "EntityCompenents/compenent.h"


struct Transform
{
    AABB collider;
    Vector2 velocity;
};

class Entity//base 
{
private:
    std::vector<std::unique_ptr<int>> compenents;
public:
    Transform transform;//Transform is also serialized


public:
    Entity() = default;

    //Compenent related
    
    template<typename T>
    T* getCompenent()
    {
        static_assert(std::is_base_of<Compenent,T>::value,"Not a compenent!\n");
        for(auto& c : compenents)
        {
            T* comp = dynamic_cast<T*>(c.get());
            if(comp)
            {
                return *comp;
            }
        }
        return nullptr;
    }

    template<typename T>
    T* addCompenent()
    {
        static_assert(std::is_base_of<Compenent,T>::value,"Not a compenent!\n");
        if(getCompenent<T>())
        {
            //Compenent already exist so we return a nullptr
            return nullptr;
        }
        auto tmp = std::make_unique<T>(this);
        auto tmp_ = tmp.get();
        compenents.push_back(tmp);
        return tmp_;
    }
    //

    void serialize(Message&);
    Entity(Message&);//desarialize constructor

    static std::unique_ptr<Entity> deserialize(Message);
};

#endif