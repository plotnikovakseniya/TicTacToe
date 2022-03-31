#pragma once

#include "clientmanager.h"

class Client : public net::ClientManager
{
    Q_OBJECT
public:
    static Client& instance();

private:
    Client();
    virtual bool handlePackage(net::Package& package) override;
};
