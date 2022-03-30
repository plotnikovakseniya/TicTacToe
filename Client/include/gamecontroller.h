#pragma once
#include <QObject>
#include <QQmlEngine>
#include "gamemodel.h"
#include "clientsettings.h"

class GameController : public QObject
{
    Q_OBJECT
public:

    explicit GameController(ClientSettings::GameTheme theme = ClientSettings::GameTheme::Dark, QObject* parent = nullptr);
    ~GameController();
    static void registerMe(const std::string& modulesName);
    Q_INVOKABLE GameModel* gameModel();
    Q_INVOKABLE ClientSettings* clientSettings() const;

private:
    GameModel m_gameModel;
    ClientSettings* m_clientSettings;
};
