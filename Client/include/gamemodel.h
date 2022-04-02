#pragma once

#include <QObject>
#include <QAbstractListModel>
#include <QQmlEngine>
#include "gameboard.h"
#include "gametypes.h"

class GameModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int dimension READ dimension CONSTANT)
public:
    explicit GameModel(tictactoe::Dimension dimension = 3, QObject *parent = nullptr);

    static void registerMe(const std::string& moduleName);

    enum GameModelRoles {
        CageText = Qt::ItemDataRole::UserRole + 1
    };

    Q_INVOKABLE bool updateGameField(int index);
    QVariant data(const QModelIndex& index, int role) const override;
    int rowCount(const QModelIndex& parent) const override;
    QHash<int, QByteArray> roleNames() const override;
    tictactoe::Dimension dimension() const;
    void setGameBoard(tictactoe::GameBoard *newGameBoard);

    void setPlayer(tictactoe::CageValue newPlayer);

signals:

private:
    tictactoe::Dimension m_dimension;
    tictactoe::GameBoard* m_gameBoard;
    tictactoe::CageValue m_player;
    std::map<tictactoe::CageValue, char> m_cageValueSign;
};
