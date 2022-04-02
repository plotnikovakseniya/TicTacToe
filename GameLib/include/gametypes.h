#pragma once

#include <vector>
namespace tictactoe
{

using Dimension = unsigned int;
using Row = unsigned int;
using Column = unsigned int;
using CageIndex = unsigned int;

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
