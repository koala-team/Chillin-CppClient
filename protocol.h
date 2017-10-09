#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <QObject>
#include <QQueue>

#include "network.h"
#include "helpers/parser.h"
#include "helpers/messages.h"


namespace koala { namespace chillin { namespace client {

class Protocol : public QObject
{
    Q_OBJECT
public:
    Protocol(Network *network, QObject *parent = 0);

    void sendMessage(const ks::KSObject *msg) const;
    ParsedMessage *recvMessage();

private slots:
    void dataReceived(const std::string &data);

signals:
    void messageReceived() const;

private:
    Parser *parser;
    Network *network;
    QQueue<ParsedMessage*> messageReceiveQueue;
};

}}}

#endif // PROTOCOL_H
