#include "gameboard.h"
#include <algorithm>

namespace tictactoe
{

GameBoard::GameBoard(Dimension dimension)
    : m_dimension {dimension},
      m_nextMove {CageValue::FirstPlayer},
      m_gameBoard {m_dimension*m_dimension, CageValue::Empty}
{
}

GameBoard::GameState GameBoard::updateGameBoard(Row row, Column column, CageValue value)
{
    if (m_gameState != GameState::Continue)
        return m_gameState;

    CageIndex ind = row * m_dimension + column;

    if (value == CageValue::Empty ||
        row > m_dimension - 1 || column > m_dimension - 1 ||
        m_gameBoard.at(ind) != CageValue::Empty ||
        m_nextMove != value)
    {
        m_gameState = GameState::Error;
        return m_gameState;
    }

    m_gameBoard.at(ind) = value;
    m_nextMove = (m_nextMove == CageValue::FirstPlayer) ?
                CageValue::SecondPlayer :
                CageValue::FirstPlayer;

    m_gameState = checkGameState();

    return m_gameState;
}

GameBoard::GameState GameBoard::winner(CageValue value) const
{
    if (value == CageValue::FirstPlayer)
    {
        return GameState::FirstPlayerWin;
    }
    if (value == CageValue::SecondPlayer)
    {
        return GameState::SecondPlayerWin;
    }
    return GameState::Continue;
}

GameBoard::GameState GameBoard::gameState() const
{
    return m_gameState;
}

GameBoard::GameState GameBoard::checkGameState() const
{
    if (m_gameState != GameState::Continue)
        return m_gameState;

    // check by row
    for (auto rowBegin = m_gameBoard.begin();
         rowBegin < m_gameBoard.end();
         rowBegin += m_dimension)
    {
        if (std::equal(rowBegin + 1, rowBegin + m_dimension, rowBegin) &&
                *rowBegin != CageValue::Empty)
        {
            return winner(*rowBegin);
        }
    }

    // check by column
    bool gameEnd;
    for (auto columnBegin = m_gameBoard.begin();
         columnBegin < m_gameBoard.begin() + m_dimension;
         columnBegin += 1)
    {
        if (*columnBegin != CageValue::Empty)
        {
            gameEnd = true;
            for (auto columnIter = columnBegin + m_dimension;
                 columnIter < m_gameBoard.end() && gameEnd;
                 columnIter += m_dimension)
            {
                if (*columnIter != *columnBegin)
                {
                    gameEnd = false;
                }
            }
            if (gameEnd)
                return winner(*columnBegin);
        }
    }

    // check main diagonal
    gameEnd = true;
    if (*m_gameBoard.begin() != CageValue::Empty)
    {
        for (auto diagIter = m_gameBoard.begin() + m_dimension + 1;
             diagIter < m_gameBoard.end() && gameEnd;
             diagIter += m_dimension + 1)
        {
            if (*diagIter != *m_gameBoard.begin())
            {
                gameEnd = false;
            }
        }
        if (gameEnd)
            return winner(*m_gameBoard.begin());
    }

    // check secondary diagonal
    gameEnd = true;
    if (*(m_gameBoard.begin() + m_dimension - 1) != CageValue::Empty)
    {
        const auto& diagStart = m_gameBoard.begin() + m_dimension - 1;
        for (auto diagIter = diagStart + m_dimension - 1;
             diagIter < m_gameBoard.end() - m_dimension + 1 && gameEnd;
             diagIter += m_dimension - 1)
        {
            if (*diagIter != *(m_gameBoard.begin() + m_dimension - 1))
            {
                gameEnd = false;
            }
        }
        if (gameEnd)
            return winner(*m_gameBoard.begin());
    }

    // check empty cages
    if (std::find(m_gameBoard.begin(),
                  m_gameBoard.end(),
                  CageValue::Empty) != m_gameBoard.end())
        return GameState::Continue;

    // no winner, no empty cages => it's a draw
    return GameState::Draw;
}

}
