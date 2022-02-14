#include "gamecontrollerbase.h"

GameControllerBase::GameControllerBase(GameTheme theme, QObject* parent)
    : QObject(parent),
      m_theme {theme}
{

}

void GameControllerBase::registerMe(const std::string& moduleName)
{
    qmlRegisterType<GameControllerBase>(moduleName.c_str(), 1, 0, "GameControllerBase");
}

int GameControllerBase::theme() const
{
    return m_theme;
}

QString GameControllerBase::themeName() const
{
    switch(m_theme) {
    case Dark: {
        return "Dark";
    }
    case Light: {
        return "Light";
    }
    default: {
        return "";
    }
    }
}

void GameControllerBase::setTheme(int newTheme)
{
    if (m_theme == newTheme)
        return;

    m_theme = static_cast<GameTheme>(newTheme);
    emit themeChanged();
}
