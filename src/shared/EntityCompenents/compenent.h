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
    bool isUpdated = false;
    Entity* entity;

protected:
    Compenent(Entity*);
public:
    virtual void Update();
    virtual void Serialize(Message&);

	static void SerializeAll(std::vector<std::unique_ptr<Compenent>>&,Message&);
/*[GeneratedField START]*/
public:
	static void DeserializeAll(Entity*,Message&);

protected:
	void Serialize_(Message&);
public:
	void Deserialize(Message&);
	void Start();
/*[GeneratedField END]*/
};

#endif