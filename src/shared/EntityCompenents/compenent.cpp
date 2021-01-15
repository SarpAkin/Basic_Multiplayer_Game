#include "compenent.h"

#include "../entity.h"

Compenent::Compenent(Entity* e)
{
    entity = e;
}

void Compenent::Serialize(Message& m)
{

}