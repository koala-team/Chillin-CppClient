#include "core.h"

#include <thread>

#include <QThread>

#include "config.h"
#include "helpers/logger.h"

using namespace ks;
using namespace ks::messages;


namespace koala { namespace chillin { namespace client {

Core::Core(QObject *parent):
    QObject(parent),
    gameRunning(false)
{
    network = new Network(this);
    protocol = new Protocol(network, this);
}

Core::~Core()
{
    delete protocol;
    delete network;
}

void Core::registerAI(AbstractAI *ai)
{
    ai->setCommandSendQueue(&commandSendQueue);
    this->ai = ai;
}


bool Core::connectToServer()
{
    auto netConfig = Config::instance()->getConfig().value("net").toObject();
    auto max_tries = netConfig.value("max_tries").toInt();
    int retry_waiting_time = netConfig.value("retry_waiting_time").toDouble() * 1000.;

    while (true)
    {
        if (network->secureConnect())
            return true;

        max_tries--;
        if (max_tries <= 0)
            break;
        Logger::instance()->log(QString("Reconnecting in %1 seconds ...").arg(
            netConfig.value("retry_waiting_time").toDouble()
        ));
        QThread::msleep(retry_waiting_time);
    }

    return false;
}

bool Core::joinGame()
{
    auto generalConfig = Config::instance()->getConfig().value("general").toObject();
    auto aiConfig = Config::instance()->getConfig().value("ai").toObject();

    KSObject *joinMessage;

    if (generalConfig.value("offline_mode").toBool())
    {
        JoinOfflineGame *msg = new JoinOfflineGame();
        msg->team_nickname(aiConfig.value("team_nickname").toString().toStdString());
        msg->agent_name(aiConfig.value("agent_name").toString().toStdString());
        joinMessage = (KSObject*) msg;
    }
    else
    {
        JoinOnlineGame *msg = new JoinOnlineGame();
        msg->token(aiConfig.value("token").toString().toStdString());
        msg->agent_name(aiConfig.value("agent_name").toString().toStdString());
        joinMessage = (KSObject*) msg;
    }

    sendMessage(joinMessage);
    ClientJoined *clientJoinedMessage;
    while (true)
    {
        ParsedMessage *msg = protocol->recvMessage();
        if (msg->message->name() == ClientJoined::nameStatic())
        {
            clientJoinedMessage = (ClientJoined*) msg->message;
            break;
        }
    }

    if (clientJoinedMessage->joined())
    {
        ai->setSides(clientJoinedMessage->sides(), clientJoinedMessage->side_name());
        Logger::instance()->succeed("Joined the game successfully");
        return true;
    }

    Logger::instance()->err("Failed to join the game");
    return false;
}

void Core::loop()
{
    bool running = true;
    while (running)
    {
        ParsedMessage *msg = protocol->recvMessage();
        if (dynamic_cast<BaseSnapshot*> (msg->message))
            handleSnapshot(msg);
        else if (msg->message->name() == StartGame::nameStatic())
            handleStartGame(msg);
        else if (msg->message->name() == EndGame::nameStatic())
        {
            handleEndGame(msg);
            running = false;
        }
        delete msg;
    }
}

void Core::handleSnapshot(const ParsedMessage *msg)
{
    auto aiConfig = Config::instance()->getConfig().value("ai").toObject();
    auto create_new_thread = aiConfig.value("create_new_thread").toBool();

    BaseSnapshot *x = (BaseSnapshot*) msg->message;
    ai->update(x);

    if (!gameRunning)
    {
        gameRunning = true;
        ai->initialize();
        if (!create_new_thread || ai->allowedToDecide())
        {
            std::thread t(&AbstractAI::decide, ai);
            t.detach();
        }
    }
    if (create_new_thread && ai->allowedToDecide())
    {
        std::thread t(&AbstractAI::decide, ai);
        t.detach();
    }
}

void Core::handleStartGame(const ParsedMessage *msg)
{
    std::thread t(&Core::sendCommandThread, this);
    t.detach();
}

void Core::handleEndGame(const ParsedMessage *msg)
{
    EndGame *x = (EndGame*) msg->message;

    QString winner = QString::fromStdString(x->winner_sidename());
    if (!x->has_winner_sidename() || winner == "")
        winner = "draw";

    Logger::instance()->log(QString("Winner side: %1").arg(winner));
    if (x->has_details() && x->details().size())
    {
        Logger::instance()->log("Details:");
        for (auto detail : x->details())
        {
            Logger::instance()->log(QString("  %1:").arg(
                QString::fromStdString(detail.first)
            ));
            for (auto sideval : detail.second)
                Logger::instance()->log(QString("    %1 -> %2").arg(
                    QString::fromStdString(sideval.first),
                    QString::fromStdString(sideval.second)
                ));
        }
    }

    quit();
}


void Core::sendMessage(const KSObject *msg)
{
    protocol->sendMessage(msg);
}

void Core::sendCommandThread()
{
    while (true)
    {
        BaseCommand *msg;
        commandSendQueue.wait_dequeue(msg);
        if (!msg)
            break;
        if (gameRunning)
            sendMessage(msg);
        delete msg;
    }
}

void Core::quit()
{
    gameRunning = false;
    commandSendQueue.enqueue(0);
    network->stop();
}

}}}
