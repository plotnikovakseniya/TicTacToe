#include "gamemodel.h"

GameModel::GameModel(tictactoe::Dimension dimension, QObject *parent)
    : QAbstractListModel {parent},
      m_dimension {dimension},
      m_gameBoard {nullptr},
      m_player {tictactoe::CageValue::Empty}
{
    m_cageValueSign = {{tictactoe::CageValue::Empty, ' '},
                       {tictactoe::CageValue::FirstPlayer, 'X'},
                       {tictactoe::CageValue::SecondPlayer, 'O'}};
}

void GameModel::registerMe(const std::string& moduleName)
{
    qmlRegisterType<GameModel>(moduleName.c_str(), 1, 0, "GameModel");
}

bool GameModel::updateGameField(int ind)
{
    if (m_gameBoard != nullptr)
    {
        beginResetModel();
        m_gameBoard->updateGameBoard(ind / m_dimension,
                                     ind % m_dimension,
                                     m_player);
        endResetModel();
        return true;
    }
    // emit dataChanged(index(ind), index(ind));

    return false;
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
        if (m_gameBoard != nullptr)
            return QVariant::fromValue(QString(m_cageValueSign.at(m_gameBoard->cageValue(rowIndex))));
        else
            return QVariant::fromValue(QString(" "));
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

void GameModel::setGameBoard(tictactoe::GameBoard* newGameBoard)
{
    m_gameBoard = newGameBoard;
}

void GameModel::setPlayer(tictactoe::CageValue newPlayer)
{
    m_player = newPlayer;
}

int GameModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return static_cast<int>(m_dimension * m_dimension);
}
