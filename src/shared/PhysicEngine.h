#ifndef PhysicsEngine_H
#define PhysicsEngine_H

#include <memory>
#include <vector>
#include <map>

#include "vector2.h"
#include "entity.h"

void simulatePhysics(std::vector<std::pair<int, std::shared_ptr<Entity>>>& entities, float deltaT);
void simulatePhysics(std::vector<std::pair<int, std::shared_ptr<Entity>>>& entities, float deltaT,Entity& player);//the client side version
#endif