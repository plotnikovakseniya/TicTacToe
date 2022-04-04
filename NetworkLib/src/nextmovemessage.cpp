#include "nextmovemessage.h"

namespace net
{

NextMoveMessage::NextMoveMessage(tictactoe::GameId gameId,
                                 tictactoe::CageIndex index,
                                 QObject* parent)
    : QObject {parent},
      m_gameId {gameId},
      m_index {index}
{
}

NextMoveMessage::NextMoveMessage(const NextMoveMessage &request)
    : QObject {request.parent()},
      m_gameId {request.gameId()},
      m_index {request.index()}
{

}

NextMoveMessage::~NextMoveMessage()
{
}

tictactoe::GameId NextMoveMessage::gameId() const
{
    return m_gameId;
}

tictactoe::CageIndex NextMoveMessage::index() const
{
    return m_index;
}

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

void operator <<(QVariant& data, const NextMoveMessage& request)
{
    QVariantMap map;
    map["gameId"] << request.m_gameId;
    map["index"] << request.m_index;
    data << map;
}

void operator >>(const QVariant& data, NextMoveMessage& request)
{
    QVariantMap map;
    data >> map;
    map["gameId"] >> request.m_gameId;
    map["index"] >> request.m_index;
}

QDataStream& operator <<(QDataStream& stream,
                         const NextMoveMessage& request)
{
    QVariant var;
    var << request;
    return stream << var;
}

QDataStream& operator >>(QDataStream& stream, NextMoveMessage& request)
{
    QVariant var;
    stream >> var;
    var >> request;
    return stream;
}

}
