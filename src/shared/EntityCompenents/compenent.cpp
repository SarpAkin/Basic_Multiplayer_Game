#include "compenent.h"

#include "allCompenent.h"
#include "../entity.h"

Compenent::Compenent(Entity* e)
{
    entity = e;
}

void Compenent::Serialize(Message& m)
{

}
/*[GeneratedField START]*/
void Compenent::SerializeAll(std::vector<std::unique_ptr<Compenent>>& comps,Message& m)
{
	for(auto& comp : comps)
		comp->Serialize(m);
}

void Compenent::DeserializeAll(Entity* e,Message& m)
{
	while(m.data.size() >= sizeof(compenentTypes))
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
}/*[GeneratedField END]*/