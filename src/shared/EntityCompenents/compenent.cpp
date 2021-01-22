#include "compenent.h"

#include "allCompenent.h"
#include "../entity.h"

/*
Compenent::Compenent(Entity* e)
{
    entity = e;
}
*/
void Compenent::Start()
{

}

void Compenent::Update()
{
	
}

void Compenent::SerializeAll(std::vector<std::unique_ptr<Compenent>>& comps,Message& m)
{
	for(auto& comp : comps)
		if(comp->isUpdated)
			comp->Serialize(m);
}

/*[GeneratedField START]*/
void Compenent::Serialize(Message& m)
{
	m.push_back_(compenentTypes::Compenent_);
	Serialize_(m);
}

void Compenent::Serialize_(Message& m)
{
}

void Compenent::Deserialize(Message& m)
{
}

Compenent::Compenent(Entity* e)
{
	Start();
}

void Compenent::DeserializeAll(Entity* e,Message& m)
{
	while(m.size() >= sizeof(compenentTypes))
	{
		auto compType = m.pop_front<compenentTypes>();
		switch(compType)
		{
			case compenentTypes::TestCompenent_:
			e->getCompenent<TestCompenent>().Deserialize(m);
			break;

			default:
			std::cout << "invalid compenent Type! " << (int)compType << '\n';
			break;
		}
	}
}
/*[GeneratedField END]*/