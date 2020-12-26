#ifndef MESSAGE_TYPES_H
#define MESSAGE_TYPES_H

#include "message.h"
#include "entity.h"

enum class MessageTypes
{
    EntitySpwaned,EntityMoved,Ping,RequestEntitySpawn,PlayerJoined,ReplyEntityRequest
};

#endif