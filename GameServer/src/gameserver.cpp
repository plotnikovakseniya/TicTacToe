#include "gameserver.h"
#include <QTcpSocket>

GameServer::GameServer(const net::ConnectionSettings& serverAddress)
      : net::ServerManager {serverAddress}
{

}

void GameServer::onClientDisconnected()
{
    QObject* senderObject = sender();
    QTcpSocket* socket {qobject_cast<QTcpSocket*>(senderObject)};

    if (!socket)
    {
        return;
    }

    m_waitingClients.remove(socket);
    for (auto it = m_playingClients.begin(); it != m_playingClients.end(); ++it)
    {
        QTcpSocket* player1, *player2;
        std::tie(player1, player2) = it->second;
        if (player1 == socket || player2 == socket)
        {
            QTcpSocket* receiver = player1 == socket ? player1 : player2;
            // TODO: send game end
        }
    }
}

void GameServer::connectSocketSignals(QTcpSocket* socket)
{
    connect(socket, &QAbstractSocket::disconnected,
            this, &GameServer::onClientDisconnected);
}

bool GameServer::handlePackage(net::Package &package, QTcpSocket *socket)
{
    if (!net::ServerManager::handlePackage(package, socket))
    {
        return false;
    }

    switch (package.type())
    {
    case net::PackageType::GAME_START_REQUEST:
    {
        if (m_waitingClients.size() > 0)
        {
            // find patner
            m_playingClients[nextGameId] = {socket, m_waitingClients.front()};
            m_waitingClients.pop_front();
            m_currentGames[nextGameId] = tictactoe::GameBoard();
            ++nextGameId;

            // TODO: select gamer for first move
            // TODO: send GAME START to players
        }
        else
        {
            m_waitingClients.push_back(socket);
        }
        break;
    }
    case net::PackageType::GAME_END_REQUEST:
    {
        // send GAME_END_REQUEST to patner
        // upload data to DB
        break;
    }
    case net::PackageType::NEXT_MOVE_REQUEST:
    {
        // check is move correct
        // update game field
        // notify the patner
        // send response
        break;
    }
    default: {
        qWarning() << "Invalid package recieved!";
        return false;
    }
    }
    return true;
}
