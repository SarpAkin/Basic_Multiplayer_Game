#include "PhysicEngine.h"

inline bool isOverLapping(const AABB& a, const AABB& b)
{
    return a.cord.x < (b.cord.x + b.size.x) && (a.cord.x + a.size.x) > b.cord.x && a.cord.y < (b.cord.y + b.size.y) && (a.cord.y + a.size.y) > b.cord.y;
}

bool simulateColidingEntity(Transform& current, Transform& other, float deltaT)
{
    Vector2 cordDiff = current.GetMidPoint() - other.GetMidPoint();
    Vector2 sizeSum = (current.collider.size + other.collider.size) / 2;
    Vector2 AbsCollisionDepth = sizeSum - Vector2(std::abs(cordDiff.x), std::abs(cordDiff.y));

    Vector2 totalDisplacement;
    if (AbsCollisionDepth.x > AbsCollisionDepth.y)
        if (cordDiff.y > 0)
            totalDisplacement.y = AbsCollisionDepth.y;
        else
            totalDisplacement.y = -AbsCollisionDepth.y;
    else
        if (cordDiff.x > 0)
            totalDisplacement.x = AbsCollisionDepth.x;
        else
            totalDisplacement.x = -AbsCollisionDepth.x;

    totalDisplacement += totalDisplacement * (((current.bouncieness + other.bouncieness) / 2 - 1) / deltaT);

    if (other.inversemass == 0)
    {
        current.collider.cord += totalDisplacement;
        return false;
    }
    else if (current.inversemass == 0)
    {
        other.collider.cord += totalDisplacement;
    }
    else
    {
        float totalmass = current.getMass() + other.getMass();
        current.collider.cord += totalDisplacement * (other.getMass() / totalmass);
        current.collider.cord += totalDisplacement * (current.getMass() / totalmass);
    }
    return true;
}

#ifndef CLIENT_SIDE
void simulatePhysics(std::vector<std::pair<int, std::shared_ptr<Entity>>>& entities, float deltaT)
#else
void simulatePhysics(std::vector<std::pair<int, std::shared_ptr<Entity>>>& entities, float deltaT, Entity& player)
#endif
{
    auto end = entities.end();
    #ifndef CLIENT_SIDE
    for (auto it = entities.begin();it != end;++it)

    #endif
    {
        #ifndef CLIENT_SIDE
        Transform& current = it->second->transform;
        Entity& current_e = *(it->second);
        if (current.inversemass == 0 || !current.isServerSide)
            continue;
        #else
        Transform& current = player.transform;
        Entity& current_e = player;
        #endif

        Vector2 beginPos = current.collider.cord;

        Vector2 acceleration = current.velocity * -current.drag + current.staticForces;
        current.velocity += acceleration * deltaT;
        current.collider.cord += current.velocity * deltaT;

        for (auto it_ = entities.begin();it_ != end;++it_)
        {
            #ifndef CLIENT_SIDE

            if (it == it_)
                continue;
            #endif

            Transform& other = it_->second->transform;
            if (isOverLapping(current.collider, other.collider))
            {
                it_->second->didMove = simulateColidingEntity(current, other, deltaT);
            }
        }

        if (std::abs(current.velocity.x) < 0.1f)
        {
            current.velocity.x = 0;
        }

        if (std::abs(current.velocity.y) < 0.1f)
        {
            current.velocity.y = 0;
        }

        if (beginPos == current.collider.cord)
        {
            current_e.didMove = true;
        }

    }
}

#ifdef CLIENT_SIDE
void simulatePhysics(std::vector<std::pair<int, std::shared_ptr<Entity>>>& entities, float deltaT)
{
    //leave mepty
}
#else
void simulatePhysics(std::vector<std::pair<int, std::shared_ptr<Entity>>>& entities, float deltaT, Entity& player)
{
    //leave empty
}
#endif