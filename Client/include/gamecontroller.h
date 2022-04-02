#pragma once

#include <QObject>
#include <QQmlEngine>
#include "gamemodel.h"
#include "clientsettings.h"
#include "client.h"
#include "gameboard.h"

class GameController : public QObject
{
    Q_OBJECT
public:

    explicit GameController(ClientSettings::GameTheme theme = ClientSettings::GameTheme::Dark,
                            QObject* parent = nullptr);
    ~GameController();
    Q_INVOKABLE GameModel* gameModel();
    Q_INVOKABLE ClientSettings* clientSettings() const;
    static void registerMe(const std::string& modulesName);
    bool setConnectionSettings(const net::ConnectionSettings& connectionSettings);
private:
    Client& m_client;
    GameModel m_gameModel;
    ClientSettings* m_clientSettings;
    tictactoe::GameBoard* m_localGameBoard;
private slots:
    void onGameEnd(tictactoe::GameState state);
};
