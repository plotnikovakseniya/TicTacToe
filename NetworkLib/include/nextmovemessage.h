#pragma once

#include "../shared/include/gametypes.h"
#include <QObject>
#include <QVariant>

namespace net
{

class NextMoveMessage : public QObject
{
    Q_OBJECT
public:
    NextMoveMessage(tictactoe::GameId gameId = 0,
                    tictactoe::CageIndex index = 0,
                    QObject* parent = nullptr);

    NextMoveMessage(const NextMoveMessage& request);
    ~NextMoveMessage();

    friend void operator <<(QVariant& data, const NextMoveMessage& request);
    friend void operator >>(const QVariant& data, NextMoveMessage& request);
    friend QDataStream& operator >>(QDataStream& stream,
                                    NextMoveMessage& request);
    friend QDataStream& operator <<(QDataStream& stream,
                                    const NextMoveMessage& request);


    tictactoe::GameId gameId() const;

    tictactoe::CageIndex index() const;

protected:
    tictactoe::GameId m_gameId;
    tictactoe::CageIndex m_index;
};

}

Q_DECLARE_METATYPE(net::NextMoveMessage)
