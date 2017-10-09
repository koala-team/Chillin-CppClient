#include "protocol.h"

#include <QEventLoop>

#include "helpers/logger.h"

using namespace std;


namespace koala { namespace chillin { namespace client {

Protocol::Protocol(Network *network, QObject *parent):
    QObject(parent),
    network(network)
{
    connect(
        network, SIGNAL(dataReceived(std::string)),
        this, SLOT(dataReceived(std::string))
    );
}

void Protocol::sendMessage(const ks::KSObject *msg) const
{
    string data = parser->encode(msg);
    network->sendData(data);
}

ParsedMessage *Protocol::recvMessage()
{
    if (messageReceiveQueue.empty())
    {
        QEventLoop loop;
        loop.connect(this, SIGNAL(messageReceived()), SLOT(quit()));
        loop.exec();
    }
    return messageReceiveQueue.dequeue();
}

void Protocol::dataReceived(const string &data)
{
    try
    {
        ParsedMessage *msg = parser->decode(data);
        messageReceiveQueue.enqueue(msg);
        emit messageReceived();
    }
    catch(ParseException &e)
    {
        Logger::instance()->warn(e.what());
    }
}

}}}
