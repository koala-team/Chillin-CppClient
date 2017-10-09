#ifndef GAMECLIENT_H
#define GAMECLIENT_H

#include <string>

#include "core.h"
#include "abstract_ai.h"


namespace koala { namespace chillin { namespace client {

class GameClient
{
public:
    GameClient(const std::string &cfgPath = "");
    ~GameClient();

    void registerAI(AbstractAI *ai);
    void run();

private:
    Core *core;
};

}}}

#endif // GAMECLIENT_H
