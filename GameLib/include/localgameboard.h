#pragma once

#include <vector>
#include <QObject>
#include "gametypes.h"
#include "gameboardinterface.h"
#include "gamelib_global.h"

namespace tictactoe
{

class GAME_LIB_EXPORT LocalGameBoard : public GameBoardInterface
{
    Q_OBJECT
public:
    LocalGameBoard(Dimension dimension = 3);

    void newGame(Dimension dimension = 3) override;
    GameState move(Row row, Column column, CageValue value) override;
    GameState move(CageIndex ind, CageValue value) override;
    GameState gameState() const override;
    CageValue cageValue(Row row, Column column) const override;
    CageValue cageValue(CageIndex index) const override;
    CageValue operator[](CageIndex index) const override;

protected:
    GameState winner(CageValue value) const;
    GameState checkGameState() const;
};

}
