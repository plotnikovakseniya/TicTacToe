#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QQmlEngine>

class GameModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int dimension READ dimension CONSTANT)
public:
    explicit GameModel(size_t dimension = 3, QObject *parent = nullptr);

    static void registerMe(const std::string& moduleName);

    QVariant data(const QModelIndex& index, int role) const override;
    int rowCount(const QModelIndex& parent) const override;

    size_t dimension() const;
signals:

private:
    size_t m_dimension;
};

#endif // GAMEMODEL_H
