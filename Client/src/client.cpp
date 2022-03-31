#include "client.h"

Client::Client()
{
    connectSocketSignals();
}

bool Client::handlePackage(net::Package &package)
{
    return ClientManager::handlePackage(package);
}

Client &Client::instance()
{
    static Client instance;
    return instance;
}
