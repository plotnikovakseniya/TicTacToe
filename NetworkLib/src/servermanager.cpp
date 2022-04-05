#include "servermanager.h"
#include "networktypes.h"
#include <QTcpSocket>

namespace net
{

ServerManager::ServerManager(const net::ConnectionSettings& serverAddress)
    : m_serverAddress {serverAddress}
{
    ServerManager::connectSignals();
    const bool listenResult {m_server.listen(m_serverAddress.address(), m_serverAddress.port())};

    if (!listenResult)
    {
        qCritical() << "Cannot initialize server! Not started!";
    }
}

void ServerManager::onNewConnection()
{
    qDebug() << "New connection!";
    QTcpSocket* clientConnection = m_server.nextPendingConnection();
    if (clientConnection)
    {
        ServerManager::connectSocketSignals(clientConnection);
        m_clients.push_back(clientConnection);
    }
}

void ServerManager::onClientDisconnected()
{
    QObject* senderObject = sender();
    QTcpSocket* socket {qobject_cast<QTcpSocket*>(senderObject)};

    if (!socket)
    {
        return;
    }

    m_clients.erase(std::remove(m_clients.begin(), m_clients.end(), socket),
                    m_clients.end());
    socket->deleteLater();
    qDebug() << "Client disconnected!";
}

void ServerManager::onDataArrived()
{
    QObject* senderObject = sender();
    QTcpSocket* socket {qobject_cast<QTcpSocket*>(senderObject)};

    if (!socket)
    {
        return;
    }

    QDataStream in {socket};
    in.setVersion(QDataStream::Qt_DefaultCompiledVersion);

    forever {
        in.startTransaction();

        net::Package inputPackage;
        in >> inputPackage;

        if (!in.commitTransaction())
        {
            break;
        }

        handlePackage(inputPackage, socket);
    }
}

void ServerManager::notify(const net::Package &package, QTcpSocket *socket)
{
    if (socket)
    {
        socket->write(package.rawData());
    }
}

bool ServerManager::sendPackage(Package &package, QTcpSocket *socket) const
{
    const bool isConnected {std::find(m_clients.begin(), m_clients.end(), socket) != m_clients.end()};
    if (isConnected)
    {
        socket->write(package.rawData());
        // socket->flush();
        socket->waitForBytesWritten();
        qDebug() << "Send package with type " << static_cast<int>(package.type());
    }

    return isConnected;
}

bool ServerManager::handlePackage(net::Package &package, QTcpSocket *socket)
{
    if (!socket)
    {
        qWarning() << "Package handle failed: null socket!";
        return false;
    }

    qDebug() << "Recieved package with type " << static_cast<int>(package.type());

    return true;
}

void ServerManager::connectSignals()
{
    connect(&m_server, &QTcpServer::newConnection,
            this, &ServerManager::onNewConnection);
}

void ServerManager::connectSocketSignals(QTcpSocket* socket)
{
    connect(socket, &QAbstractSocket::disconnected,
            this, &ServerManager::onClientDisconnected);
    connect(socket, &QAbstractSocket::readyRead,
            this, &ServerManager::onDataArrived);
}

}
