#pragma once

#include "servermanager.h"
#include "gameboardinterface.h"

class GameServer : public net::ServerManager
{
    Q_OBJECT
public:
    GameServer(const net::ConnectionSettings& serverAddress);
    ~GameServer();
protected slots:
    virtual void onClientDisconnected() override;
    virtual void connectSocketSignals(QTcpSocket* socket) override;
protected:
    virtual bool handlePackage(net::Package& package, QTcpSocket* socket) override;
    std::list<QTcpSocket*> m_waitingClients;
    std::map<tictactoe::GameId, std::pair<QTcpSocket*,QTcpSocket*>> m_playingClients;
    std::map<tictactoe::GameId, tictactoe::GameBoardInterface*> m_currentGames;
    tictactoe::GameId m_nextGameId;
};
