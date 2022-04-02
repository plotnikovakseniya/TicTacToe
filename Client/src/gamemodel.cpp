#include "gamemodel.h"

GameModel::GameModel(tictactoe::Dimension dimension, QObject *parent)
    : QAbstractListModel {parent},
      tictactoe::GameBoard {dimension}
{
    m_cageValueSign = {{CageValue::Empty, ' '}, {CageValue::FirstPlayer, 'X'}, {CageValue::SecondPlayer, 'O'}};
}

void GameModel::registerMe(const std::string& moduleName)
{
    qmlRegisterType<GameModel>(moduleName.c_str(), 1, 0, "GameModel");
}

bool GameModel::updateGameField(int ind)
{
    tictactoe::Row row = ind / m_dimension;
    tictactoe::Column column = ind % m_dimension;
    beginResetModel();
    GameBoard::updateGameBoard(row, column, m_nextMove);
    endResetModel();

    // emit dataChanged(index(ind), index(ind));

    return true;
}

QHash<int, QByteArray> GameModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[GameModelRoles::CageText] = "cagetext";

    return roles;
}

QVariant GameModel::data(const QModelIndex& index, int role) const
{
    int rowIndex = index.row();

    if (!index.isValid() || rowIndex > rowCount(index))
    {
        return {};
    }

    switch (role)
    {
    case GameModelRoles::CageText:
    {
        return QVariant::fromValue(QString(m_cageValueSign.at(m_gameBoard[rowIndex])));
        // return QVariant::fromValue(QString("X"));
    }
    default:
    {
        qWarning() << "Invalid role passed!";
        return {};
    }
    }

    return {};
}

tictactoe::Dimension GameModel::dimension() const
{
    return m_dimension;
}

int GameModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return static_cast<int>(m_dimension * m_dimension);
}
