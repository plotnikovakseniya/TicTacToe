#pragma once
#include <QTcpServer>
#include <QSettings>
#include "package.h"

namespace net
{

class ServerManager : public QObject
{
    Q_OBJECT
public:
    ServerManager(const QHostAddress& address, const Port& port);

private slots:
    virtual void onNewConnection();
    virtual void onClientDisconnected();
    virtual void onDataArrived();
    virtual void notify(const net::Package& package, QTcpSocket* socket);

protected:
    QTcpServer m_server;
    QHostAddress m_address;
    Port m_port;
    std::vector<QTcpSocket*> m_clients;

    virtual bool handlePackage(net::Package& package, QTcpSocket* socket);
    virtual void connectSignals();
    virtual void connectSocketSignals(QTcpSocket* socket);
};

}
