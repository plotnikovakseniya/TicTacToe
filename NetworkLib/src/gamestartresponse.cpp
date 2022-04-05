#include "gamestartresponse.h"
#include "networktypes.h"

namespace net
{

GameStartResponse::GameStartResponse(tictactoe::GameId gameId,
                                     tictactoe::CageValue player,
                                     QObject* parent)
    : QObject {parent},
      m_gameId {gameId},
      m_player {player}
{
}

GameStartResponse::GameStartResponse(const GameStartResponse& request)
    : QObject {request.parent()},
      m_gameId {request.gameId()},
      m_player {request.player()}
{

}

GameStartResponse::~GameStartResponse()
{
}

tictactoe::GameId GameStartResponse::gameId() const
{
    return m_gameId;
}

tictactoe::CageValue GameStartResponse::player() const
{
    return m_player;
}

void operator <<(QVariant& data, const GameStartResponse& request)
{
    QVariantMap map;
    map["gameId"] << request.gameId();
    map["player"] << static_cast<unsigned int>(request.player());
    data << map;
}

void operator >>(const QVariant& data, GameStartResponse& request)
{
    QVariantMap map;
    data >> map;
    map["gameId"] >> request.m_gameId;
    map["player"] >> request.m_player;
}

QDataStream& operator <<(QDataStream& stream,
                         const GameStartResponse& request)
{
    QVariant var;
    var << request;
    return stream << var;
}

QDataStream& operator >>(QDataStream& stream, GameStartResponse& request)
{
    QVariant var;
    stream >> var;
    var >> request;
    return stream;
}

}
