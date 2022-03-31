#include "nnserver.h"

NNServer::NNServer(const net::ConnectionSettings& serverAddress)
      : net::ServerManager {serverAddress}
{

}

bool NNServer::handlePackage(net::Package &package, QTcpSocket *socket)
{
    return true;
}
