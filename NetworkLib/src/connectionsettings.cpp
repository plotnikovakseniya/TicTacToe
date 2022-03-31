#include "connectionsettings.h"

namespace net
{

ConnectionSettings::ConnectionSettings()
{
    m_address = QHostAddress {""};
    m_port = 0;
}

ConnectionSettings::ConnectionSettings(const QString& networkSettingsFile,
                                       const QString& settingsName,
                                       const QSettings::Format& format)
{
    qDebug() << "Network settings file: " << networkSettingsFile;

    // TODO: add check NETWORK_SETTINGS_FILE exists

    QSettings settings(networkSettingsFile, format);
    settings.beginGroup(settingsName);

    // TODO: add check QHostAddress and Port are correct

    m_address = QHostAddress {settings.value("IPAddress").toString()};
    m_port = settings.value("Port").value<net::Port>();

    qDebug() << "IP address: " << m_address;
    qDebug() << "port: " << m_port;

    settings.endGroup();
}

const QHostAddress& ConnectionSettings::address() const
{
    return m_address;
}

Port ConnectionSettings::port() const
{
    return m_port;
}

}
