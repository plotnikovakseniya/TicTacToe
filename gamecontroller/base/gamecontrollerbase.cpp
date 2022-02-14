#include "gamecontrollerbase.h"

GameControllerBase::GameControllerBase(QObject* parent)
    : QObject(parent)
{

}

void GameControllerBase::registerMe(const std::string& moduleName)
{
    qmlRegisterType<GameControllerBase>(moduleName.c_str(), 1, 0, "GameControllerBase");
}

GameControllerBase::GameTheme GameControllerBase::theme() const
{
    return m_theme;
}

void GameControllerBase::setTheme(GameTheme newTheme)
{
    m_theme = newTheme;
}
