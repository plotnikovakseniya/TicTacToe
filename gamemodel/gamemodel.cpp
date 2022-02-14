#include "gamemodel.h"

GameModel::GameModel(size_t dimension, QObject *parent)
    : QAbstractListModel{parent},
      m_dimension {dimension}
{

}

void GameModel::registerMe(const std::string& moduleName)
{
    qmlRegisterType<GameModel>(moduleName.c_str(), 1, 0, "GameModel");
}

QVariant GameModel::data(const QModelIndex& index, int role) const
{
    Q_UNUSED(role)
    Q_UNUSED(index)
//    int rowIndex = index.row();

//    if (!index.isValid() || rowIndex > rowCount(index))
//    {
//        return {};
//    }

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
