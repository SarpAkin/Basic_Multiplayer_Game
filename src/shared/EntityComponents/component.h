#ifndef COMPENENT_H
#define COMPENENT_H

#include <vector>
#include <memory>

#include "../message.h"
#include "componentTypes.h"

class Entity;

//Base component class
class Component
{
    friend Entity;
protected:
    bool isUpdated = false;
    Entity* entity;

protected:
    Component(Entity*);
    virtual void OnSync();
public:
    virtual void Update();
    virtual void Serialize(Message&);

	static void SerializeAll(std::vector<std::unique_ptr<Component>>&,Message&);
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