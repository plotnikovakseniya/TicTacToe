#include "gamecontroller.h"

GameController::GameController(GameTheme theme, QObject* parent)
    : QObject(parent),
      m_theme {theme}
{

}

void GameController::registerMe(const std::string& moduleName)
{
    qmlRegisterType<GameController>(moduleName.c_str(), 1, 0, "GameController");
}

int GameController::theme() const
{
    return m_theme;
}

void GameController::setTheme(int newTheme)
{
    if (m_theme == newTheme)
        return;

    m_theme = static_cast<GameTheme>(newTheme);
    emit themeChanged();
}

void GameController::switchTheme()
{
    m_theme = static_cast<GameTheme>(static_cast<int>(!m_theme));
    emit themeChanged();
}

GameModel *GameController::gameModel()
{
    return &m_gameModel;
}
