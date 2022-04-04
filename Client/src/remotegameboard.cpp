#include "remotegameboard.h"
#include "nextmovemessage.h"
#include "gamestartresponse.h"

RemoteGameBoard::RemoteGameBoard()
    : tictactoe::GameBoardInterface {tictactoe::GameState::Error, 1},
      m_gameId {0},
      m_player {tictactoe::CageValue::Empty},
      m_partner {tictactoe::CageValue::Empty}
{
    connectSocketSignals();
}

bool RemoteGameBoard::handlePackage(net::Package &package)
{
    if (ClientManager::handlePackage(package))
    {
        switch (package.type())
        {
            case (net::PackageType::GAME_BOARD_UPDATE_NOTIFY):
            {
                net::NextMoveMessage notify;
                package.data() >> notify;
                m_gameBoard.at(notify.index()) = m_partner;
                emit gameBoardUpdated();
                return true;
            }
            case (net::PackageType::GAME_START_RESPONSE):
            {
                if (m_gameState != tictactoe::GameState::Continue)
                {
                    m_gameState = tictactoe::GameState::Continue;
                    net::GameStartResponse response;
                    package.data() >> response;
                    m_nextMove = tictactoe::CageValue::FirstPlayer;
                    m_player = response.player();
                    m_gameId = response.gameId();
                    m_partner = m_player == tictactoe::CageValue::FirstPlayer ?
                                tictactoe::CageValue::SecondPlayer :
                                tictactoe::CageValue::FirstPlayer;
                    qDebug() << "New game with id:" << response.gameId();
                }
                break;
            }
            default:
            {
                qWarning() << "Cannot handle package with type" << static_cast<int>(package.type());
                return false;
            }
        }
        return true;
    }
    return false;
}

RemoteGameBoard& RemoteGameBoard::instance()
{
    static RemoteGameBoard instance;
    return instance;
}

tictactoe::GameState RemoteGameBoard::gameState() const
{
    return m_gameState;
}

void RemoteGameBoard::setupGameBoard(tictactoe::Dimension dimension)
{
    m_gameBoard.clear();
    m_gameBoard.resize(dimension * dimension, tictactoe::CageValue::Empty);
    m_dimension = dimension;
}

void RemoteGameBoard::newGame(tictactoe::Dimension dimension)
{
    setupGameBoard(dimension);
    net::Package package {QVariant{}, net::PackageType::GAME_START_REQUEST};
    sendPackage(package);
}

tictactoe::CageValue RemoteGameBoard::cageValue(tictactoe::CageIndex index) const
{
    return m_gameBoard.at(index);
}

tictactoe::CageValue RemoteGameBoard::cageValue(tictactoe::Row row, tictactoe::Column column) const
{
    return m_gameBoard.at(row * m_dimension + column);
}

tictactoe::CageValue RemoteGameBoard::operator[](tictactoe::CageIndex index) const
{
    return m_gameBoard.at(index);
}

tictactoe::GameState RemoteGameBoard::move(tictactoe::Row row,
                                           tictactoe::Column column,
                                           tictactoe::CageValue value)
{
    return move(row * m_dimension + column, value);
}

tictactoe::GameState RemoteGameBoard::move(tictactoe::CageIndex index,
                           tictactoe::CageValue value)
{
    if (value == m_player && m_gameState == tictactoe::GameState::Continue)
    {
        Q_UNUSED(value);
        net::NextMoveMessage request {m_gameId, index};
        QVariant data;
        data << request;
        net::Package package {data, net::PackageType::NEXT_MOVE_REQUEST};
        if (sendPackage(package))
        {
            // TODO: move to NEXT_MOVE_RESPONSE
            m_gameBoard.at(index) = m_player;
            return tictactoe::GameState::Continue;
        }
    }
    return m_gameState;
}
