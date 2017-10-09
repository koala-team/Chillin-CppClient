#include "gameclient.h"

#include "config.h"


namespace koala { namespace chillin { namespace client {

GameClient::GameClient(const std::string &cfgPath)
{
    Config::instance()->initialize(QString::fromStdString(cfgPath));
    core = new Core();
}

GameClient::~GameClient()
{
    delete core;
}

void GameClient::registerAI(AbstractAI *ai)
{
    core->registerAI(ai);
}


void GameClient::run()
{
    if (!core->connectToServer())
        return ;
    if (!core->joinGame())
        return ;
    core->loop();
}

}}}
