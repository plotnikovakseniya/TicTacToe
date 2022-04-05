#pragma once
#include <QtGlobal>
#include <QHostAddress>
#include <climits>
#include "../shared/include/gametypes.h"

namespace net
{
    const tictactoe::CageIndex RESPONSE_OK = std::numeric_limits<tictactoe::CageIndex>::max();

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

    template<typename T>
    void operator <<(QVariant& data, const T& target)
    {
        data = QVariant::fromValue<T>(target);
    }

    template<typename T>
    void operator >>(const QVariant& data, T& target)
    {
        target = data.value<T>();
    }
}

Q_DECLARE_METATYPE(net::PackageType)
Q_DECLARE_METATYPE(net::ConnectionState)
