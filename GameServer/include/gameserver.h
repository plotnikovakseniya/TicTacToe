#pragma once

#include "servermanager.h"

class GameServer : public net::ServerManager
{
    Q_OBJECT
public:
    GameServer(const net::ConnectionSettings& serverAddress);
protected:
    virtual bool handlePackage(net::Package& package, QTcpSocket* socket) override;
};
