#ifndef ENTITY_H
#define ENTITY_H

#include <type_traits>
#include <vector>
#include <memory>

#include "message.h"
#include "vector2.h"
#include "dynamic_ptr_cast.h"

#include "EntityComponents/component.h"

struct Transform
{
    AABB collider;
    Vector2 velocity;
};

class Entity//base 
{
private:
    std::vector<std::unique_ptr<Component>> components;
public:
    Transform transform;//Transform is also serialized
    bool didMove = false;

public:
    Entity() = default;

    //Component related
    
    template<typename T>
    T& getComponent()//returns the spesified component if it doesn't exist creates one and returns it
    {
        static_assert(std::is_base_of<Component,T>::value,"Not a component!\n");
        for(auto& c : components)
        {
            T* comp = dynamic_cast<T*>(c.get());
            if(comp)
            {
                return *comp;
            }
        }
        std::unique_ptr<T> tmp = std::make_unique<T>(this);
        T& tmp_ = *tmp;
        components.push_back(dynamic_ptr_cast<Component>(std::move(tmp)));
        return tmp_;
    }

    /*
    template<typename T>
    T* addComponent()
    {
        static_assert(std::is_base_of<Component,T>::value,"Not a component!\n");
        if(getComponent<T>())
        {
            //Component already exist so we return a nullptr
            return nullptr;
        }
        auto tmp = std::make_unique<T>(this);
        auto tmp_ = tmp.get();
        components.push_back(tmp);
        return tmp_;
    }
    */
    //

    bool serialize(Message&);
    void Deserialize(Message&);
    Entity(Message&);//desarialize constructor

    static std::unique_ptr<Entity> deserialize(Message);
};

#endif