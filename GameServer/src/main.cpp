#include "gameserver.h"
#include <QCoreApplication>

int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);

    GameServer server { net::ConnectionSettings {NETWORK_SETTINGS_FILE, "GameServer"} };

    return app.exec();
}
