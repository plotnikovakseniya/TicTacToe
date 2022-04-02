#pragma once

#include "servermanager.h"
#include "gameboard.h"

class GameServer : public net::ServerManager
{
    Q_OBJECT
public:
    GameServer(const net::ConnectionSettings& serverAddress);
protected slots:
    virtual void onClientDisconnected() override;
    virtual void connectSocketSignals(QTcpSocket* socket) override;
protected:
    using GameId = unsigned int;

    virtual bool handlePackage(net::Package& package, QTcpSocket* socket) override;
    std::list<QTcpSocket*> m_waitingClients;
    std::map<GameId, std::pair<QTcpSocket*,QTcpSocket*>> m_playingClients;
    std::map<GameId, tictactoe::GameBoard> m_currentGames;
    GameId nextGameId;
};
