#include "gamecontroller.h"

GameController::GameController(ClientSettings::GameTheme theme,
                               QObject* parent)
    : QObject {parent},
      m_client {Client::instance()},
      m_clientSettings {ClientSettings::getClientSettings(theme)},
      m_localGameBoard {nullptr}
{
    // m_client.setConnectionSettings(net::ConnectionSettings {NETWORK_SETTINGS_FILE, "GameServer"});
    m_localGameBoard = new tictactoe::GameBoard();
    m_gameModel.setGameBoard(m_localGameBoard);
    m_gameModel.setPlayer(tictactoe::FirstPlayer);
    connect(m_localGameBoard, &tictactoe::GameBoard::gameEnd, this, &GameController::onGameEnd);
}

void GameController::registerMe(const std::string& moduleName)
{
    qmlRegisterType<GameController>(moduleName.c_str(), 1, 0, "GameController");
}

GameModel* GameController::gameModel()
{
    return &m_gameModel;
}

ClientSettings* GameController::clientSettings() const
{
    return m_clientSettings;
}

GameController::~GameController()
{
    if (m_clientSettings != nullptr)
        delete m_clientSettings;
    if (m_localGameBoard != nullptr)
        delete m_localGameBoard;
}

bool GameController::setConnectionSettings(const net::ConnectionSettings& connectionSettings)
{
    m_client.setConnectionSettings(connectionSettings);
    return true;
}

void GameController::onGameEnd(tictactoe::GameState state)
{
    qDebug() << state;
}
