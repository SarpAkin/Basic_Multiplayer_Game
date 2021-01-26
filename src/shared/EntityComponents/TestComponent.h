#ifndef TCOMP
#define TCOMP

#include "component.h"

struct testStruct
{
    float* ptr;
/*[GeneratedField START]*//*[GeneratedField END]*/};


class TestComponent : public Component
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
	TestComponent(Entity*);
	void Serialize(Message&) override;
	void Deserialize(Message&);
	void Start();
/*[GeneratedField END]*/
};

#endif