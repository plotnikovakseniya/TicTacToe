#pragma once

#include <vector>
#include <QObject>

namespace tictactoe
{

using Dimension = unsigned int;
using Row = unsigned int;
using Column = unsigned int;
using CageIndex = unsigned int;
using GameId = unsigned int;

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

}

Q_DECLARE_METATYPE(tictactoe::CageValue)
Q_DECLARE_METATYPE(tictactoe::GameState)
