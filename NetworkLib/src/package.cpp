#include "package.h"
#include "nextmovemessage.h"
#include "gamestartresponse.h"
#include <QDebug>

namespace net
{

Package::Package(PackageType type)
                : m_translationStream {&m_rawData, QIODevice::WriteOnly},
                  m_type {type}
{
    m_translationStream.setVersion(QDataStream::Qt_DefaultCompiledVersion);
}

Package::Package(const QVariant &data, PackageType type)
                 : Package(type)
{
    m_data = data;
    fillTranslationStream();
}

Package::Package(const Package& package)
                 : Package(package.type())
{
    m_data = package.data();
    fillTranslationStream();
}

PackageType Package::type() const
{
    return m_type;
}

QVariant Package::data() const
{
    return m_data;
}

QByteArray Package::rawData() const
{
    return m_rawData;
}

QDataStream& operator>>(QDataStream &stream, net::Package &package)
{
    qint32 type;
    stream >> type;
    package.m_type = static_cast<PackageType>(type);

    QVariant data;
    stream >> data;
    package.m_data = data;

    package.fillTranslationStream();

    return stream;
}

void Package::fillTranslationStream()
{
    switch (m_type)
    {
        case (net::PackageType::NEXT_MOVE_REQUEST):
        {
            m_translationStream << m_type;
            net::NextMoveMessage request;
            m_data >> request;
            m_translationStream << request;
            break;
        }
        case (net::PackageType::GAME_START_REQUEST):
        {
            m_translationStream << m_type;
            m_translationStream << m_data;
            break;
        }
        case (net::PackageType::GAME_START_RESPONSE):
        {
            m_translationStream << m_type;
            net::GameStartResponse response;
            m_data >> response;
            m_translationStream << response;
            break;
        }
        case (net::PackageType::GAME_BOARD_UPDATE_NOTIFY):
        {
            m_translationStream << m_type;
            net::NextMoveMessage notify;
            m_data >> notify;
            m_translationStream << notify;
            break;
        }
        default:
        {
            qWarning() << "Can't translate package with type " << static_cast<int>(m_type);
        }
    }
}
}
