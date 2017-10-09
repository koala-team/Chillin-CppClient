#ifndef CORE_H
#define CORE_H

#include <QObject>

#include "network.h"
#include "protocol.h"
#include "abstract_ai.h"
#include "helpers/messages.h"
#include "helpers/blockingconcurrentqueue.h"


namespace koala { namespace chillin { namespace client {

class Core : public QObject
{
    Q_OBJECT
public:
    Core(QObject *parent = 0);
    ~Core();

    void registerAI(AbstractAI *ai);
    bool connectToServer();
    bool joinGame();
    void loop();

private:
    void handleSnapshot(const ParsedMessage *msg);
    void handleStartGame(const ParsedMessage *msg);
    void handleEndGame(const ParsedMessage *msg);

private:
    void sendMessage(const ks::KSObject *msg);
    void sendCommandThread();
    void quit();

private:
    bool gameRunning;
    Network *network;
    Protocol *protocol;
    AbstractAI *ai;
    moodycamel::BlockingConcurrentQueue<ks::messages::BaseCommand*> commandSendQueue;
};

}}}

#endif // CORE_H
