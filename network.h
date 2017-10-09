#ifndef NETWORK_H
#define NETWORK_H

#include <QtNetwork/QSslSocket>


namespace koala { namespace chillin { namespace client {

class Network : public QObject
{
    Q_OBJECT
public:
    Network(QObject *parent = 0);
    ~Network();

    bool secureConnect(const bool &async = false);
    void stop();
    bool isConnected() const;
    void sendData(const std::string &data) const;

signals:
    void dataReceived(const std::string &data) const;
    void stopped() const;
    void connected() const;
    void notConnected() const;

private slots:
    void encrypted();
    void stateChanged(QAbstractSocket::SocketState state);
    void sslErrors(const QList<QSslError> &errors) const;
    void readyRead();

private:
    QSslSocket *socket;
    bool socketConnected;
    unsigned int readSize;
    std::string readBuffer;
};

}}}

#endif // NETWORK_H
