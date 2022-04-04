#pragma once

#include "../shared/include/gametypes.h"
#include <QObject>
#include <QVariant>

namespace net
{

class GameStartResponse : public QObject
{
    Q_OBJECT
public:
    GameStartResponse(tictactoe::GameId gameId = 0,
                      tictactoe::CageValue player = tictactoe::CageValue::FirstPlayer,
                      QObject* parent = nullptr);

    GameStartResponse(const GameStartResponse& request);
    ~GameStartResponse();

    friend void operator <<(QVariant& data, const GameStartResponse& request);
    friend void operator >>(const QVariant& data, GameStartResponse& request);
    friend QDataStream& operator >>(QDataStream& stream,
                                    GameStartResponse& request);
    friend QDataStream& operator <<(QDataStream& stream,
                                    const GameStartResponse& request);


    tictactoe::GameId gameId() const;
    tictactoe::CageValue player() const;

protected:
    tictactoe::GameId m_gameId;
    tictactoe::CageValue m_player;
};

}

Q_DECLARE_METATYPE(net::GameStartResponse)
