#pragma once

#include <QObject>
#include <QAbstractListModel>
#include <QQmlEngine>
#include "gameboard.h"

class GameModel : public QAbstractListModel,
                  public tictactoe::GameBoard
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
    bool updateGameField();
    tictactoe::Dimension dimension() const;
signals:

private:
    std::map<CageValue, char> m_cageValueSign;
};
