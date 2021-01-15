//Only include it once

#define IS_SERVER_SIDE 0

//includes
#include <memory>
#include <vector>
#include <map>

#include "vector2.h"
#include "entity.h"

void simulatePhysics(std::map<int,std::unique_ptr<Entity>>& entities)
{
    auto end = entities.end();
    for(auto it = entities.begin();it != end;++it)
    {
        
    }
}