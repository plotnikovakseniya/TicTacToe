#pragma once

#include <vector>
#include <QObject>
#include "gametypes.h"

namespace tictactoe
{

class GameBoardInterface : public QObject
{
    Q_OBJECT
public:
    GameBoardInterface(GameState gameState = GameState::Error,
                       Dimension dimension = 0,
                       CageValue nextMove = CageValue::Empty)
        : m_gameState {gameState},
          m_dimension {dimension},
          m_nextMove {nextMove},
          m_gameBoard {dimension*dimension, CageValue::Empty}
    {
    }
    virtual ~GameBoardInterface(){};

    virtual Dimension dimension() const {return m_dimension;};
    virtual GameState gameState() const {return m_gameState;};
    virtual CageValue nextMove() const {return m_nextMove;};

    virtual void newGame(Dimension dimension = 3) = 0;

    virtual GameState move(Row row, Column column, CageValue value) = 0;
    virtual GameState move(CageIndex ind, CageValue value) = 0;
    virtual CageValue cageValue(Row row, Column column) const = 0;
    virtual CageValue cageValue(CageIndex index) const = 0;
    virtual CageValue operator[](CageIndex index) const = 0;

signals:
    void gameBoardUpdated();
    void gameEnd(tictactoe::GameState state);

protected:
    GameState m_gameState;
    Dimension m_dimension;
    CageValue m_nextMove;
    std::vector<CageValue> m_gameBoard;
};

}

Q_DECLARE_INTERFACE(tictactoe::GameBoardInterface, "GameBoardInterface")
