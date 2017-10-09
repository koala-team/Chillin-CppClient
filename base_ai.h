#ifndef BASE_AI_H
#define BASE_AI_H

#include <vector>
#include <string>

#include "abstract_ai.h"
#include "helpers/messages.h"
#include "helpers/blockingconcurrentqueue.h"


namespace koala { namespace chillin { namespace client {

// definition

template <class T>
class BaseAI : public AbstractAI
{
public:
    BaseAI(T world);
    ~BaseAI();

    virtual void update(const ks::messages::BaseSnapshot *snapshot);
    virtual bool allowedToDecide() const;
    virtual void decide() = 0;

protected:
    virtual void sendCommandInternal(const ks::KSObject *command, ks::messages::BaseCommand *msg = 0);
    void sendCommand(ks::KSObject *command);

protected:
    T world;
};


// implementation

template <class T>
BaseAI<T>::BaseAI(T world):
    world(world)
{
}

template <class T>
BaseAI<T>::~BaseAI()
{
}


template <class T>
void BaseAI<T>::update(const ks::messages::BaseSnapshot *snapshot)
{
    world->deserialize(snapshot->world_payload());
}

template <class T>
bool BaseAI<T>::allowedToDecide() const
{
    return true;
}

template <class T>
void BaseAI<T>::sendCommandInternal(const ks::KSObject *command, ks::messages::BaseCommand *msg)
{
    ks::messages::BaseCommand *message;

    if (msg == 0)
        message = new ks::messages::BaseCommand();
    else
        message = (ks::messages::BaseCommand*) msg;

    message->type(command->name());
    message->payload(command->serialize());
    commandSendQueue->enqueue(message);
}

template <class T>
void BaseAI<T>::sendCommand(ks::KSObject *command)
{
    if (allowedToDecide())
        sendCommandInternal(command);
}

}}}

#endif // BASE_AI_H
