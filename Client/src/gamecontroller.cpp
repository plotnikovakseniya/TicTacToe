#include "gamecontroller.h"

GameController::GameController(ClientSettings::GameTheme theme, QObject* parent)
    : QObject {parent},
      m_client {Client::instance()},
      m_clientSettings {ClientSettings::getClientSettings(theme)}
{
    setConnectionSettings();
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

bool GameController::setConnectionSettings()
{
    qDebug() << "Network settings file: " << NETWORK_SETTINGS_FILE;

    // TODO: add check NETWORK_SETTINGS_FILE exists

    QSettings settings(NETWORK_SETTINGS_FILE, QSettings::IniFormat);
    settings.beginGroup("GameServer");

    // TODO: add check QHostAddress and Port are correct

    m_client.setConnectionSettings( net::ConnectionSettings {
                                        QHostAddress {settings.value("IPAddress").toString()},
                                        settings.value("Port").value<net::Port>() });
    qDebug() << "New connection settings";
    qDebug() << "IP address: " << settings.value("IPAddress").toString();
    qDebug() << "Port: " << settings.value("Port").toString();
    settings.endGroup();
    return true;
}
