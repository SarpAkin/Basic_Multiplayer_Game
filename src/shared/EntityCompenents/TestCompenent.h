#ifndef TCOMP
#define TCOMP

#include "compenent.h"

struct testStruct
{
    float* ptr;
/*[GeneratedField START]*//*[GeneratedField END]*/};


class TestCompenent : public Compenent
{
    private:
    /*[{serializeable]*/
    float f;
    int i;
    testStruct ptr;
    /*[serializeable}]*/
/*[GeneratedField START]*/
protected:
	void Serialize_(Message&);
public:
	TestCompenent(Entity*);
	void Serialize(Message&) override;
	void Deserialize(Message&);
	void Start();
/*[GeneratedField END]*/
};

#endif