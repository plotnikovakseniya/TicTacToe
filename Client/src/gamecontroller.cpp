#include "gamecontroller.h"
#include "remotegameboard.h"
#include "clientmanager.h"

GameController::GameController(ClientSettings::GameTheme theme,
                               QObject* parent)
    : QObject {parent},
      m_client {Client::instance()},
      m_clientSettings {ClientSettings::getClientSettings(theme)},
      m_gameBoard {nullptr}
{
    // m_client.setConnectionSettings(net::ConnectionSettings {NETWORK_SETTINGS_FILE, "GameServer"});
    // m_gameBoard = new tictactoe::GameBoard();
    m_gameBoard = &RemoteGameBoard::instance();
    dynamic_cast<net::ClientManager*>(m_gameBoard)->setConnectionSettings(
                net::ConnectionSettings {NETWORK_SETTINGS_FILE, "GameServer"});
    m_gameModel.setGameBoard(m_gameBoard);
    m_gameModel.setPlayer(tictactoe::FirstPlayer);
    connect(m_gameBoard, &tictactoe::GameBoardInterface::gameEnd,
            this, &GameController::onGameEnd);
    connect(m_gameBoard, &tictactoe::GameBoardInterface::gameBoardUpdated,
            &m_gameModel, &GameModel::onGameBoardUpdated);

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

void GameController::newGame()
{
    m_gameModel.newGame();
}

GameController::~GameController()
{
    if (m_clientSettings != nullptr)
        delete m_clientSettings;
    if (m_gameBoard != nullptr)
        delete m_gameBoard;
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
