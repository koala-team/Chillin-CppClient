#ifndef TURNBASED_AI_H
#define TURNBASED_AI_H

#include <vector>

#include "realtime_ai.h"


namespace koala { namespace chillin { namespace client {

// definition

template <class T>
class TurnbasedAI : public RealtimeAI<T>
{
public:
    TurnbasedAI(T world);
    ~TurnbasedAI();

    virtual void update(const ks::messages::BaseSnapshot *snapshot);
    virtual bool allowedToDecide() const;

protected:
    virtual void sendCommandInternal(const ks::KSObject *command, ks::messages::BaseCommand *msg = 0);

protected:
    std::vector<std::string> turnAllowedSides;
};


// implementation

template <class T>
TurnbasedAI<T>::TurnbasedAI(T world):
    RealtimeAI<T>(world)
{
}

template <class T>
TurnbasedAI<T>::~TurnbasedAI()
{
}


template <class T>
void TurnbasedAI<T>::update(const ks::messages::BaseSnapshot *snapshot)
{
    RealtimeAI<T>::update(snapshot);

    ks::messages::TurnbasedSnapshot *x = (ks::messages::TurnbasedSnapshot*) snapshot;
    turnAllowedSides = x->turn_allowed_sides();
}

template <class T>
bool TurnbasedAI<T>::allowedToDecide() const
{
    return std::find(turnAllowedSides.begin(), turnAllowedSides.end(), this->mySide)
           != turnAllowedSides.end();
}

template <class T>
void TurnbasedAI<T>::sendCommandInternal(const ks::KSObject *command, ks::messages::BaseCommand *msg)
{
    ks::messages::TurnbasedCommand *message;
    if (msg == 0)
        message = new ks::messages::TurnbasedCommand();
    else
        message = (ks::messages::TurnbasedCommand*) msg;
    RealtimeAI<T>::sendCommandInternal(command, message);
}

}}}

#endif // TURNBASED_AI_H
