#include "nnserver.h"
#include <QCoreApplication>

int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);
    NNServer server { net::ConnectionSettings { QHostAddress {"127.0.0.1"}, 8080 } };

    return app.exec();
}
