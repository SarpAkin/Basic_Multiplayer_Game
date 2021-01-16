#include "compenent.h"

class TestCompenent : Compenent
{
    private:
    /*[{serializeable]*/
    float f;
    int i;

    /*[serializeable}]*/
/*[GeneratedField START]*/public:
	void Serialize(Message&);
	void Deserialize(Message&);
/*[GeneratedField END]*/};