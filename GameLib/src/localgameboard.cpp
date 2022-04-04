#include "localgameboard.h"
#include <algorithm>

namespace tictactoe
{

LocalGameBoard::LocalGameBoard(Dimension dimension)
    : GameBoardInterface {GameState::Continue, dimension, CageValue::FirstPlayer}
{
}

void LocalGameBoard::newGame(Dimension dimension)
{
    m_dimension = dimension;
    m_gameBoard.clear();
    m_gameBoard.resize(dimension * dimension, tictactoe::CageValue::Empty);
    m_gameState = GameState::Continue;
    m_nextMove = CageValue::FirstPlayer;
}

GameState LocalGameBoard::move(Row row, Column column, CageValue value)
{
    if (m_gameState != GameState::Continue)
        return m_gameState;

    if (row > m_dimension - 1 || column > m_dimension - 1)
    {
        m_gameState = GameState::Error;
        emit gameEnd(m_gameState);
        return m_gameState;
    }

    return move(row * m_dimension + column, value);
}

GameState LocalGameBoard::move(CageIndex ind, CageValue value)
{
    if (m_gameState != GameState::Continue)
        return m_gameState;

    if (value == CageValue::Empty ||
        m_gameBoard.at(ind) != CageValue::Empty ||
        m_nextMove != value)
    {
        m_gameState = GameState::Error;
        emit gameEnd(m_gameState);
        return m_gameState;
    }

    m_gameBoard.at(ind) = value;
    m_nextMove = (m_nextMove == CageValue::FirstPlayer) ?
                CageValue::SecondPlayer :
                CageValue::FirstPlayer;

    m_gameState = checkGameState();
    if (m_gameState != GameState::Continue)
        emit gameEnd(m_gameState);

    return m_gameState;
}

GameState LocalGameBoard::winner(CageValue value) const
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

GameState LocalGameBoard::gameState() const
{
    return m_gameState;
}

CageValue LocalGameBoard::cageValue(Row row, Column column) const
{
    return m_gameBoard[row * m_dimension + column];
}

CageValue LocalGameBoard::cageValue(CageIndex index) const
{
    return m_gameBoard[index];
}

CageValue LocalGameBoard::operator[](CageIndex index) const
{
    return m_gameBoard[index];
}

GameState LocalGameBoard::checkGameState() const
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
    bool end;
    for (auto columnBegin = m_gameBoard.begin();
         columnBegin < m_gameBoard.begin() + m_dimension;
         columnBegin += 1)
    {
        if (*columnBegin != CageValue::Empty)
        {
            end = true;
            for (auto columnIter = columnBegin + m_dimension;
                 columnIter < m_gameBoard.end() && end;
                 columnIter += m_dimension)
            {
                if (*columnIter != *columnBegin)
                {
                    end = false;
                }
            }
            if (end)
            {
                return winner(*columnBegin);
            }
        }
    }

    // check main diagonal
    end = true;
    if (*m_gameBoard.begin() != CageValue::Empty)
    {
        for (auto diagIter = m_gameBoard.begin() + m_dimension + 1;
             diagIter < m_gameBoard.end() && end;
             diagIter += m_dimension + 1)
        {
            if (*diagIter != *m_gameBoard.begin())
            {
                end = false;
            }
        }
        if (end)
        {
            return winner(*m_gameBoard.begin());
        }
    }

    // check secondary diagonal
    end = true;
    if (*(m_gameBoard.begin() + m_dimension - 1) != CageValue::Empty)
    {
        const auto& diagStart = m_gameBoard.begin() + m_dimension - 1;
        for (auto diagIter = diagStart + m_dimension - 1;
             diagIter < m_gameBoard.end() - m_dimension + 1 && end;
             diagIter += m_dimension - 1)
        {
            if (*diagIter != *(m_gameBoard.begin() + m_dimension - 1))
            {
                end = false;
            }
        }
        if (end)
        {
            return winner(*(m_gameBoard.begin() + m_dimension - 1));
        }
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
