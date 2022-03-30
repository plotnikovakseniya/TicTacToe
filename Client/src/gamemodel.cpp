#include "gamemodel.h"

GameModel::GameModel(size_t dimension, QObject *parent)
    : QAbstractListModel {parent},
      m_dimension {dimension},
      m_gameBoard {m_dimension*m_dimension, CageValues::Empty}
{
    m_cageValueSign = {{CageValues::Empty, ' '}, {CageValues::FirstPlayer, 'X'}, {CageValues::SecondPlayer, 'O'}};
}

void GameModel::registerMe(const std::string& moduleName)
{
    qmlRegisterType<GameModel>(moduleName.c_str(), 1, 0, "GameModel");
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
        //char x = m_cageValueSign[CageValues::Empty];
        //return QVariant::fromValue(QString(m_cageValueSign[m_gameBoard[rowIndex]]));
        return QVariant::fromValue(QString("X"));
    }
    default:
    {
        qWarning() << "Invalid role passed!";
        return {};
    }
    }

    return {};
}

size_t GameModel::dimension() const
{
    return m_dimension;
}

int GameModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return static_cast<int>(m_dimension * m_dimension);
}
