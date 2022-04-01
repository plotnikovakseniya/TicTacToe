#pragma once

#include <vector>
namespace tictactoe
{

using Dimension = unsigned int;
using Row = unsigned int;
using Column = unsigned int;
using CageIndex = unsigned int;

class GameBoard
{
public:
    enum CageValue {
        Empty,
        FirstPlayer,
        SecondPlayer
    };

    enum GameState {
        Continue,
        FirstPlayerWin,
        SecondPlayerWin,
        Draw,
        Error
    };

    GameBoard(Dimension dimension = 3);
    GameState updateGameBoard(Row row, Column column, CageValue value);
    GameState gameState() const;
private:
    GameState winner(CageValue value) const;
    GameState checkGameState() const;
    GameState m_gameState;
    Dimension m_dimension;
    CageValue m_nextMove;
    std::vector<CageValue> m_gameBoard;
};

}
