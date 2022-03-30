#include "servermanager.h"

class GameServer : public net::ServerManager
{
    Q_OBJECT
public:
    GameServer(const QHostAddress& address, const net::Port& port);
protected:
    virtual bool handlePackage(net::Package& package, QTcpSocket* socket) override;
};
