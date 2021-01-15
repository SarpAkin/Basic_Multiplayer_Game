#ifndef COMPENENT_H
#define COMPENENT_H


class Message;
class Entity;

//Base compenent class
class Compenent
{
    friend Entity;

protected:
    Entity* entity;

protected:
    Compenent(Entity*);
public:
    virtual void Update();
    virtual void Serialize(Message&);
};

#endif