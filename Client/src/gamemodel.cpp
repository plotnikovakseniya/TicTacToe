#include "gamemodel.h"
#include "remotegameboard.h"

GameModel::GameModel(QObject *parent)
    : QAbstractListModel {parent},
      m_gameBoard {nullptr}
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
        m_gameBoard->move(ind, dynamic_cast<RemoteGameBoard*>(m_gameBoard)->player());
    }
    return true;
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
