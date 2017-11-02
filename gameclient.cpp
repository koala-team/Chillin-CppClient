#include "gameclient.h"

#include <QCoreApplication>

#include "config.h"


namespace koala { namespace chillin { namespace client {

GameClient::GameClient(const std::string &cfgPath)
{
    QString path = QString::fromStdString(cfgPath);
    if (QCoreApplication::arguments().size() > 1)
        path = QCoreApplication::arguments()[1];
    Config::instance()->initialize(path);
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
