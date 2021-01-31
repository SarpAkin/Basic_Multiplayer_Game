#include "component.h"

#include "allComponent.h"
#include "../entity.h"

/*
Component::Component(Entity* e)
{
    entity = e;
}
*/
void Component::Start()
{

}

void Component::Update()
{
	
}

void Component::SerializeAll(std::vector<std::unique_ptr<Component>>& comps,Message& m)
{
	for(auto& comp : comps)
		if(comp->isUpdated)
			comp->Serialize(m);
}

void Component::OnSync()
{
	
}

/*[GeneratedField START]*/
void Component::Serialize(Message& m)
{
	m.push_back_(componentTypes::Component_);
	Serialize_(m);
}

void Component::Serialize_(Message& m)
{
}

void Component::Deserialize(Message& m)
{
}

Component::Component(Entity* e)
{
	Start();
}

void Component::DeserializeAll(Entity* e,Message& m)
{
	while(m.size() >= sizeof(componentTypes))
	{
		auto compType = m.pop_front<componentTypes>();
		switch(compType)
		{
			case componentTypes::TestComponent_:
			{
				auto comp = e->getComponent<TestComponent>();
				comp.Deserialize(m);
				comp.OnSync();
				break;

			}
			default:
			std::cout << "invalid component Type! " << (int)compType << '\n';
			return;
			break;
		}
	}
}
/*[GeneratedField END]*/