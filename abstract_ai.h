#ifndef ABSTRACT_AI_H
#define ABSTRACT_AI_H

#include <map>
#include <vector>
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

    void setSides(const std::map<std::string, std::vector<std::string>> sides, const std::string mySide)
    {
        this->sides = sides;
        this->mySide = mySide;
        otherSides.clear();
        for (auto side : sides)
            if (side.first != mySide)
                this->otherSides.push_back(side.first);
        this->otherSide = (this->otherSides.size() == 1) ? this->otherSides[0] : "";
    }

    virtual void update(const ks::messages::BaseSnapshot *snapshot) = 0;
    virtual bool allowedToDecide() const = 0;
    virtual void decide() = 0;

protected:
    moodycamel::BlockingConcurrentQueue<ks::messages::BaseCommand*> *commandSendQueue;
    std::map<std::string, std::vector<std::string>> sides;
    std::string mySide;
    std::string otherSide;
    std::vector<std::string> otherSides;
};

}}}

#endif // ABSTRACT_AI_H
