#ifndef COMPENENT_H
#define COMPENENT_H

#include <vector>
#include <memory>

#include "../message.h"
#include "compenentTypes.h"

class Entity;

//Base compenent class
class Compenent
{
    friend Entity;

protected:
    Entity* entity;

protected:
    Compenent(Entity*);
public:
    virtual void Update();
    virtual void Serialize(Message&);

/*[GeneratedField START]*/public:
	static void SerializeAll(std::vector<std::unique_ptr<Compenent>>&,Message&);
	static void DeserializeAll(Entity*,Message&);/*[GeneratedField END]*/
};

#endif