#pragma once

#include "gametypes.h"
#include "client.h"
#include "gameboardinterface.h"

class RemoteGameBoard : public net::ClientManager,
                        public tictactoe::GameBoardInterface
{
public:
    static RemoteGameBoard& instance();
    tictactoe::GameState gameState() const override;
    void newGame(tictactoe::Dimension dimension = 3) override;
    tictactoe::GameState move(tictactoe::CageIndex index, tictactoe::CageValue value) override;
    tictactoe::GameState move(tictactoe::Row row,
                              tictactoe::Column column,
                              tictactoe::CageValue value) override;
    tictactoe::CageValue cageValue(tictactoe::CageIndex index) const override;
    tictactoe::CageValue cageValue(tictactoe::Row row, tictactoe::Column column) const override;
    virtual tictactoe::CageValue operator[](tictactoe::CageIndex index) const override;

private:
    RemoteGameBoard();
    virtual bool handlePackage(net::Package& package) override;
    void setupGameBoard(tictactoe::Dimension dimension = 3);
    tictactoe::GameId m_gameId;
    tictactoe::CageValue m_player;
    tictactoe::CageValue m_partner;
};
