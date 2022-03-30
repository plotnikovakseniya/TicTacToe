#include "servermanager.h"
#include "networktypes.h"

class NNServer : public net::ServerManager
{
    Q_OBJECT
public:
    NNServer(const QHostAddress& address, const net::Port& port);
protected:
    virtual bool handlePackage(net::Package& package, QTcpSocket* socket) override;
};
