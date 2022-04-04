#include "gamemodel.h"

GameModel::GameModel(QObject *parent)
    : QAbstractListModel {parent},
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

bool GameModel::move(int ind)
{
    if (m_gameBoard != nullptr)
    {
        beginResetModel();
        m_gameBoard->move(ind, m_player);
        endResetModel();
        return true;
    }
    // emit dataChanged(index(ind), index(ind));

    return false;
}

void GameModel::newGame(tictactoe::Dimension dimension)
{
    beginResetModel();
    m_gameBoard->newGame(dimension);
    emit dimensionChanged();
    endResetModel();
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
    return m_gameBoard->dimension();
}

void GameModel::setGameBoard(tictactoe::GameBoardInterface* newGameBoard)
{
    beginResetModel();
    m_gameBoard = newGameBoard;
    endResetModel();
}

void GameModel::setPlayer(tictactoe::CageValue newPlayer)
{
    m_player = newPlayer;
}

void GameModel::onGameBoardUpdated()
{
    beginResetModel();
    endResetModel();
}

int GameModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return static_cast<int>(m_gameBoard->dimension() * m_gameBoard->dimension());
}
