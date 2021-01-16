#include "TestCompenent.h"

/*[GeneratedField START]*/
void TestCompenent::Serialize(Message& m)
{
	m.push_back_(compenentTypes::TestCompenent_);
	m.push_back(f);
	m.push_back(i);
}

void TestCompenent::Deserialize(Message& m)
{
	f = m.pop_front<float>();
	i = m.pop_front<int>();
}
/*[GeneratedField END]*/