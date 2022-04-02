#include "nnserver.h"
#include <QCoreApplication>
#include <QDebug>

int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);
    NNServer server { net::ConnectionSettings {NETWORK_SETTINGS_FILE, "NNServer"} };

    return app.exec();
}
