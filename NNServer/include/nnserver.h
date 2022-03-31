#pragma once

#include "servermanager.h"
#include "networktypes.h"

class NNServer : public net::ServerManager
{
    Q_OBJECT
public:
    NNServer(const net::ConnectionSettings& serverAddress);
protected:
    virtual bool handlePackage(net::Package& package, QTcpSocket* socket) override;
};
