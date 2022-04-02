#pragma once

#include <vector>
#include <QObject>
#include "gametypes.h"

namespace tictactoe
{

class GameBoard : public QObject
{
    Q_OBJECT
public:
    GameBoard(Dimension dimension = 3);
    GameState updateGameBoard(Row row, Column column, CageValue value);
    GameState gameState() const;
    CageValue cageValue(Row row, Column column) const;
    CageValue cageValue(CageIndex index) const;
    CageValue operator[](CageIndex index) const;

signals:
    // void gameBoardUpdated(tictactoe::CageIndex index, tictactoe::CageValue value);
    void gameEnd(tictactoe::GameState state);

protected:
    GameState winner(CageValue value) const;
    GameState checkGameState() const;
    GameState m_gameState;
    Dimension m_dimension;
    CageValue m_nextMove;
    std::vector<CageValue> m_gameBoard;
};

}
