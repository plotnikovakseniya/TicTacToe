#include "nnserver.h"

NNServer::NNServer(const QHostAddress &address, const net::Port &port)
    : ServerManager {address, port}
{

}

bool NNServer::handlePackage(net::Package &package, QTcpSocket *socket)
{

}
