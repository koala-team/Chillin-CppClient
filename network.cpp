#include "network.h"

#include "config.h"
#include "helpers/logger.h"

using namespace std;


namespace koala { namespace chillin { namespace client {

Network::Network(QObject *parent) :
    QObject(parent),
    socketConnected(false)
{
    socket = new QSslSocket(this);
    connect(
        socket, SIGNAL(encrypted()),
        this, SLOT(encrypted())
    );
    connect(
        socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
        this, SLOT(stateChanged(QAbstractSocket::SocketState))
    );
    connect(
        socket, SIGNAL(sslErrors(QList<QSslError>)),
        this, SLOT(sslErrors(QList<QSslError>))
    );
    connect(
        socket, SIGNAL(readyRead()),
        this, SLOT(readyRead())
    );
}

Network::~Network()
{
    stop();
    delete socket;
}

bool Network::secureConnect(const bool &async)
{
    readSize = 0;
    readBuffer = "";

    auto netConfig = Config::instance()->getConfig().value("net").toObject();
    auto host = netConfig.value("host").toString();
    auto port = netConfig.value("port").toInt();
    int timeout = netConfig.value("timeout").toDouble() * 1000.;

    Logger::instance()->log(
        QString("Connecting to host '%1' port %2 ...").arg(host, QString::number(port))
    );

    socket->connectToHostEncrypted(host, port);
    if (!async)
        socket->waitForEncrypted(timeout);

    return socketConnected;
}

void Network::stop()
{
    socket->close();
    socketConnected = false;
}

bool Network::isConnected() const
{
    return socketConnected;
}


void Network::encrypted()
{
    socketConnected = true;
    Logger::instance()->succeed("Connected successfully");
    emit connected();
}

void Network::stateChanged(QAbstractSocket::SocketState state)
{
    if (state == QAbstractSocket::UnconnectedState)
    {
        if (isConnected())
        {
            stop();
            Logger::instance()->log("Connection closed");
            emit stopped();
        }
        else
        {
            Logger::instance()->err("Failed to connect: " + socket->errorString());
            emit notConnected();
        }
    }
}

void Network::sslErrors(const QList<QSslError> &errors) const
{
    auto generalConfig = Config::instance()->getConfig().value("general").toObject();
    bool offline_mode = generalConfig.value("offline_mode").toBool();
    if (offline_mode)
        socket->ignoreSslErrors();

    for (auto error: errors)
        Logger::instance()->warn("SslError: " + error.errorString());
}


void Network::readyRead()
{
    readBuffer += socket->readAll().toStdString();

    while (true)
    {
        if (readBuffer.size() < sizeof(readSize))
            break;
        if (readSize == 0)
        {
            readSize = *((unsigned int*) &readBuffer[0]);
            readBuffer.erase(0, sizeof(readSize));
        }
        if (readBuffer.size() < readSize)
            break;

        emit dataReceived(readBuffer.substr(0, readSize));
        readBuffer.erase(0, readSize);
        readSize = 0;
    }
}

void Network::sendData(const string &data) const
{
    auto size = data.size();
    char *sizeBytes = reinterpret_cast<char*>(&size);
    socket->write(
        (string(sizeBytes, sizeof(readSize)) + data).c_str(),
        data.size() + sizeof(readSize)
    );
}

}}}
