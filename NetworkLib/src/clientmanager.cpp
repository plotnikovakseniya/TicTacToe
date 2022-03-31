#include "clientmanager.h"
#include <QTimer>

namespace net
{

ClientManager::ClientManager()
    : m_state {net::ConnectionState::Disconnected},
      m_reconnectionTime {std::chrono::seconds {5}}
{
}

bool ClientManager::sendPackage(const Package &package)
{
    const bool isConnected {m_state == ConnectionState::Connected};
    if (isConnected)
    {
        m_serverSocket.write(package.rawData());
    }

    return isConnected;
}

void ClientManager::onSocketError(QAbstractSocket::SocketError socketError)
{
    qCritical() << "Socket error happened: " << socketError;

    QTimer::singleShot(m_reconnectionTime, this, &ClientManager::connectToServer);

    emit reconnectionTimerStarted();
}

void ClientManager::onSocketStateChanged(QAbstractSocket::SocketState socketState)
{
    qDebug() << "Socket state changed: " << socketState;

    switch (socketState)
    {
        case QAbstractSocket::SocketState::BoundState:
        case QAbstractSocket::SocketState::ConnectedState:
        {
            m_state = net::ConnectionState::Connected;
            break;
        }
        case QAbstractSocket::SocketState::ClosingState:
        case QAbstractSocket::SocketState::UnconnectedState:
        {
            m_state = net::ConnectionState::Disconnected;
            break;
        }
        default:
        {
            m_state = net::ConnectionState::Connecting;
        }
    }

    emit connectionStateChanged(m_state);
}

void ClientManager::onDataRecieved()
{
    QDataStream in {&m_serverSocket};
    in.setVersion(QDataStream::Qt_DefaultCompiledVersion);

    forever {
        in.startTransaction();

        net::Package inputPackage;
        in >> inputPackage;

        if (!in.commitTransaction())
        {
            break;
        }

        qDebug() << "Recieved package with type " << static_cast<int>(inputPackage.type());
        handlePackage(inputPackage);
    }
}

void ClientManager::connectToServer()
{
    qDebug() << "Connecting to server...";

    m_serverSocket.connectToHost(m_connectionSettings.address(), m_connectionSettings.port());
}

void ClientManager::connectSocketSignals()
{
    connect(&m_serverSocket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::errorOccurred),
            this, &ClientManager::onSocketError);
    connect(&m_serverSocket, &QAbstractSocket::stateChanged,
            this, &ClientManager::onSocketStateChanged);
    connect(&m_serverSocket, &QAbstractSocket::readyRead,
            this, &ClientManager::onDataRecieved);
}

bool ClientManager::handlePackage(net::Package &package)
{
    if (package.type() == PackageType::INVALID)
    {
            qWarning() << "Invalid package!";
            return false;
    }
    return true;
}

void ClientManager::setConnectionSettings(const ConnectionSettings &connectionSettings)
{
    m_connectionSettings = connectionSettings;
    connectToServer();
}

}
