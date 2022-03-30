#include "gameserver.h"

GameServer::GameServer(const QHostAddress &address, const net::Port &port)
    : net::ServerManager {address, port}
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
            //m_contactsWorker.handleContactsRequest(socket);
            break;
        }
        case net::PackageType::GAME_END_REQUEST:
        {
            //m_contactsWorker.handleContactsRequest(socket);
            break;
        }
        case net::PackageType::NEXT_MOVE_REQUEST:
        {
            //m_contactsWorker.handleContactsRequest(socket);
            break;
        }
        default: {
            qWarning() << "Invalid package recieved!";
        }
    }
}
