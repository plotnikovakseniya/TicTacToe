#pragma once

#include "networktypes.h"
#include <QSettings>

namespace net
{

class ConnectionSettings
{
public:
    ConnectionSettings();
    ConnectionSettings(const QString& networkSettingsFile,
                       const QString& settingsName,
                       const QSettings::Format& format = QSettings::IniFormat);
    const QHostAddress& address() const;
    Port port() const;

protected:
    QHostAddress m_address;
    Port m_port;
};

}
