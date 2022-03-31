#include "gamecontroller.h"

GameController::GameController(ClientSettings::GameTheme theme,
                               QObject* parent)
    : QObject {parent},
      m_client {Client::instance()},
      m_clientSettings {ClientSettings::getClientSettings(theme)}
{
    m_client.setConnectionSettings(net::ConnectionSettings {NETWORK_SETTINGS_FILE, "GameServer"});
}

void GameController::registerMe(const std::string& moduleName)
{
    qmlRegisterType<GameController>(moduleName.c_str(), 1, 0, "GameController");
}


GameModel *GameController::gameModel()
{
    return &m_gameModel;
}

ClientSettings *GameController::clientSettings() const
{
    return m_clientSettings;
}

GameController::~GameController()
{
    delete m_clientSettings;
}

bool GameController::setConnectionSettings(const net::ConnectionSettings& connectionSettings)
{
    m_client.setConnectionSettings(connectionSettings);
    return true;
}
