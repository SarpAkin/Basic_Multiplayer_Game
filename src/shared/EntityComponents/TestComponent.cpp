#include "TestComponent.h"

void TestComponent::Start()
{
	isUpdated = true;
}

/*[GeneratedField START]*/
void TestComponent::Serialize(Message& m)
{
	m.push_back_(componentTypes::TestComponent_);
	Serialize_(m);
}

void TestComponent::Serialize_(Message& m)
{
	Component::Serialize_(m);
	m.push_back(f);
	m.push_back(i);
	m.push_back(ptr);
}

void TestComponent::Deserialize(Message& m)
{
	Component::Deserialize(m);
	m.pop_front(f);
	m.pop_front(i);
	m.pop_front(ptr);
}

TestComponent::TestComponent(Entity* e)
 : Component::Component(e)
{
	entity = e;
	Start();
}
/*[GeneratedField END]*/