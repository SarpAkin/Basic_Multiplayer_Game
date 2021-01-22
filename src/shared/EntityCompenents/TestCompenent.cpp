#include "TestCompenent.h"

void TestCompenent::Start()
{
	isUpdated = true;
}

/*[GeneratedField START]*/
void TestCompenent::Serialize(Message& m)
{
	m.push_back_(compenentTypes::TestCompenent_);
	Serialize_(m);
}

void TestCompenent::Serialize_(Message& m)
{
	Compenent::Serialize_(m);
	m.push_back(f);
	m.push_back(i);
	m.push_back(ptr);
}

void TestCompenent::Deserialize(Message& m)
{
	Compenent::Deserialize(m);
	m.pop_front(f);
	m.pop_front(i);
	m.pop_front(ptr);
}

TestCompenent::TestCompenent(Entity* e)
 : Compenent::Compenent(e)
{
	entity = e;
	Start();
}
/*[GeneratedField END]*/