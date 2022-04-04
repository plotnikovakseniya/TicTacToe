#pragma once
#include <QtGlobal>
#include <QHostAddress>

namespace net
{
    enum class PackageType {
        INVALID,
        AUTH_REQUEST,
        AUTH_RESPONSE,
        GAME_START_REQUEST,
        GAME_START_RESPONSE,
        GAME_END_REQUEST,
        GAME_END_RESPONSE,
        NEXT_MOVE_REQUEST,
        NEXT_MOVE_RESPONSE,
        GAME_BOARD_UPDATE_NOTIFY,
    };

    enum class ConnectionState {
        Connected,
        Disconnected,
        Connecting
    };

    using Port = quint16;
}

Q_DECLARE_METATYPE(net::PackageType)
Q_DECLARE_METATYPE(net::ConnectionState)
