#pragma once
#include <QTcpSocket>
#include <QSettings>
#include "package.h"

namespace net
{

class ClientManager : public QObject
{
    Q_OBJECT
public:
    ClientManager();

    virtual bool sendPackage(const Package& package);
    virtual void setConnectionSettings(const ConnectionSettings& m_connectionSettings);

signals:
    void connectionStateChanged(net::ConnectionState state);
    void reconnectionTimerStarted();

protected slots:
    virtual void onSocketError(QAbstractSocket::SocketError socketError);
    virtual void onSocketStateChanged(QAbstractSocket::SocketState socketState);
    virtual void onDataRecieved();

protected:
    virtual void connectToServer();
    virtual void connectSocketSignals();
    virtual bool handlePackage(Package& package) = 0;

    ConnectionSettings m_connectionSettings;
    ConnectionState m_state;
    QTcpSocket m_serverSocket;
    std::chrono::milliseconds m_reconnectionTime;
};

}
