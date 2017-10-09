#ifndef REALTIME_AI_H
#define REALTIME_AI_H

#include "base_ai.h"


namespace koala { namespace chillin { namespace client {

// definition

template <class T>
class RealtimeAI : public BaseAI<T>
{
public:
    RealtimeAI(T world);
    ~RealtimeAI();

    virtual void update(const ks::messages::BaseSnapshot *snapshot);
    virtual bool allowedToDecide() const;

protected:
    virtual void sendCommandInternal(const ks::KSObject *command, ks::messages::BaseCommand *msg = 0);

protected:
    unsigned int currentCycle;
    float cycleDuration;
};


// implementation

template <class T>
RealtimeAI<T>::RealtimeAI(T world):
    BaseAI<T>(world)
{
}

template <class T>
RealtimeAI<T>::~RealtimeAI()
{
}


template <class T>
void RealtimeAI<T>::update(const ks::messages::BaseSnapshot *snapshot)
{
    BaseAI<T>::update(snapshot);

    ks::messages::RealtimeSnapshot *x = (ks::messages::RealtimeSnapshot*) snapshot;
    currentCycle = x->current_cycle();
    cycleDuration = x->cycle_duration();
}

template <class T>
bool RealtimeAI<T>::allowedToDecide() const
{
    return true;
}

template <class T>
void RealtimeAI<T>::sendCommandInternal(const ks::KSObject *command, ks::messages::BaseCommand *msg)
{
    ks::messages::RealtimeCommand *message;
    if (msg == 0)
        message = new ks::messages::RealtimeCommand();
    else
        message = (ks::messages::RealtimeCommand*) msg;
    message->cycle(currentCycle);
    BaseAI<T>::sendCommandInternal(command, message);
}

}}}

#endif // REALTIME_AI_H
