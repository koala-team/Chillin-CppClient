#ifndef ABSTRACT_AI_H
#define ABSTRACT_AI_H

#include <map>
#include <string>

#include "helpers/messages.h"
#include "helpers/blockingconcurrentqueue.h"


namespace koala { namespace chillin { namespace client {

class AbstractAI
{
public:
    void setCommandSendQueue(moodycamel::BlockingConcurrentQueue<ks::messages::BaseCommand*> *q)
    {
        this->commandSendQueue = q;
    }

    void setSides(const std::map<std::string, std::vector<std::string>> sides)
    {
        this->sides = sides;
    }

    void setMySide(const std::string mySide)
    {
        this->mySide = mySide;
    }

    virtual void update(const ks::messages::BaseSnapshot *snapshot) = 0;
    virtual bool allowedToDecide() const = 0;
    virtual void decide() = 0;

protected:
    moodycamel::BlockingConcurrentQueue<ks::messages::BaseCommand*> *commandSendQueue;
    std::map<std::string, std::vector<std::string>> sides;
    std::string mySide;
};

}}}

#endif // ABSTRACT_AI_H
