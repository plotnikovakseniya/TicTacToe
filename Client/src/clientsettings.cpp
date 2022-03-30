#include "clientsettings.h"

ClientSettings* ClientSettings::m_clientSettings = nullptr;

ClientSettings::ClientSettings(GameTheme theme, QObject *parent)
    : QObject{parent},
      m_theme {theme}
{

}

int ClientSettings::theme() const
{
    return static_cast<int>(m_theme);
}

void ClientSettings::registerMe(const std::string& moduleName)
{
    qmlRegisterType<ClientSettings>(moduleName.c_str(), 1, 0, "ClientSettings");
}

void ClientSettings::switchTheme()
{
    m_theme = static_cast<GameTheme>(static_cast<int>(!m_theme));
    emit themeChanged();
}

void ClientSettings::setTheme(int newTheme)
{
    m_theme = static_cast<GameTheme>(newTheme);
    emit themeChanged();
}

ClientSettings *ClientSettings::getClientSettings(GameTheme theme)
{
    if(m_clientSettings==nullptr){
            m_clientSettings = new ClientSettings(theme);
        }
    return m_clientSettings;
}
