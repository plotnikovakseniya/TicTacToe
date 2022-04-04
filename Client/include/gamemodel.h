#pragma once

#include <QObject>
#include <QAbstractListModel>
#include <QQmlEngine>
#include "gameboardinterface.h"
#include "gametypes.h"

class GameModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int dimension READ dimension NOTIFY dimensionChanged)
public:
    explicit GameModel(QObject *parent = nullptr);

    static void registerMe(const std::string& moduleName);

    enum GameModelRoles {
        CageText = Qt::ItemDataRole::UserRole + 1
    };

    Q_INVOKABLE bool move(int index);
    void newGame(tictactoe::Dimension dimension = 3);
    QVariant data(const QModelIndex& index, int role) const override;
    int rowCount(const QModelIndex& parent) const override;
    QHash<int, QByteArray> roleNames() const override;
    tictactoe::Dimension dimension() const;
    void setGameBoard(tictactoe::GameBoardInterface *newGameBoard);
    void setPlayer(tictactoe::CageValue newPlayer);

public slots:
    void onGameBoardUpdated();

signals:
    void dimensionChanged();

private:
    tictactoe::GameBoardInterface* m_gameBoard;
    tictactoe::CageValue m_player;
    std::map<tictactoe::CageValue, char> m_cageValueSign;
};
