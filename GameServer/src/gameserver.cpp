#include "gameserver.h"

GameServer::GameServer(const net::ConnectionSettings& serverAddress)
      : net::ServerManager {serverAddress}
{

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
        // find patner
        // start new game
        // select gamer for first move
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
