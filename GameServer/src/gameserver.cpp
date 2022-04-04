#include "gameserver.h"
#include <QTcpSocket>
#include "nextmovemessage.h"
#include "localgameboard.h"
#include "gamestartresponse.h"

GameServer::GameServer(const net::ConnectionSettings& serverAddress)
      : net::ServerManager {serverAddress},
        m_nextGameId {1}
{

}

GameServer::~GameServer()
{
    for (auto iter = m_currentGames.begin();
         iter != m_currentGames.end();
         iter++)
    {
        delete iter->second;
    }
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
            m_playingClients[m_nextGameId] = {socket, m_waitingClients.front()};
            m_waitingClients.pop_front();
            m_currentGames[m_nextGameId] = new tictactoe::LocalGameBoard();

            net::GameStartResponse responseFirst {m_nextGameId, tictactoe::CageValue::FirstPlayer};
            QVariant dataFirst;
            dataFirst << responseFirst;
            net::Package packageFirst {dataFirst, net::PackageType::GAME_START_RESPONSE};
            sendPackage(packageFirst, m_playingClients[m_nextGameId].first);

            net::GameStartResponse responsesSecond {m_nextGameId, tictactoe::CageValue::SecondPlayer};
            QVariant dataSecond;
            dataSecond << responsesSecond;
            net::Package packageSecond {dataSecond, net::PackageType::GAME_START_RESPONSE};
            sendPackage(packageSecond, m_playingClients[m_nextGameId].second);

            qDebug() << "New game with id:" << m_nextGameId;

            ++m_nextGameId;
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
        net::NextMoveMessage request;
        package.data() >> request;
        if (m_playingClients.find(request.gameId()) == m_playingClients.end())
        {
            qWarning() << "NEXT_MOVE_REQUEST parsing: unknown gameId:" << request.gameId();
            return false;
        }

        tictactoe::CageValue value;
        QTcpSocket* partner;

        if (socket == m_playingClients.at(request.gameId()).first)
        {
            value = tictactoe::CageValue::FirstPlayer;
            partner = m_playingClients.at(request.gameId()).second;
        }
        else if (socket == m_playingClients.at(request.gameId()).second)
        {
            value = tictactoe::CageValue::SecondPlayer;
            partner = m_playingClients.at(request.gameId()).first;
        }
        else
        {
            qWarning() << "NEXT_MOVE_REQUEST parsing: unknown player!";
            return false; // TODO: error processing
        }

        if (m_currentGames.at(request.gameId())->move(request.index(), value)
                != tictactoe::GameState::Error)
        {
            QVariant data;
            data << net::NextMoveMessage {request.gameId(), request.index()};
            net::Package package {data, net::PackageType::GAME_BOARD_UPDATE_NOTIFY};
            sendPackage(package, partner);
        }
        else
        {
            qWarning() << "NEXT_MOVE_REQUEST processing: update game board failed!";
            return false; // TODO: error processing
        }
        break;
    }
    default: {
        qWarning() << "Invalid package recieved!";
        return false;
    }
    }
    return true;
}
