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

    enum GameModelRoles {
        CageText = Qt::ItemDataRole::UserRole + 1
    };

    enum CageValues {
        Empty,
        FirstPlayer,
        SecondPlayer
    };

    QVariant data(const QModelIndex& index, int role) const override;
    int rowCount(const QModelIndex& parent) const override;
    QHash<int, QByteArray> roleNames() const override;

    size_t dimension() const;
signals:

private:
    size_t m_dimension;
    std::vector<CageValues> m_gameBoard;
    std::map<CageValues, char> m_cageValueSign;
};

#endif // GAMEMODEL_H
