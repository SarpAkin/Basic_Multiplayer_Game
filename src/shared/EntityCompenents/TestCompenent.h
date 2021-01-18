#ifndef TCOMP
#define TCOMP

#include "compenent.h"

class TestCompenent : public Compenent
{
    private:
    /*[{serializeable]*/
    float f;
    int i;

    /*[serializeable}]*/
/*[GeneratedField START]*/
public:
	TestCompenent(Entity*);
	void Serialize(Message&) override;
	void Deserialize(Message&);
	void Start();
/*[GeneratedField END]*/
};

#endif