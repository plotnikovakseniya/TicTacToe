#pragma once
#include <QDataStream>
#include <QVariant>
#include "networktypes.h"
#include "netlib_global.h"

namespace net
{
class NET_LIB_EXPORT Package
{
public:
    Package(PackageType type = PackageType::INVALID);
    Package(const QVariant& data, PackageType = PackageType::INVALID);
    Package(const Package& package);

    PackageType type() const;
    QVariant data() const;
    QByteArray rawData() const;

    friend QDataStream& operator>>(QDataStream& stream, Package& package);
private:
    QByteArray m_rawData;
    QDataStream m_translationStream;

    PackageType m_type;
    QVariant m_data;

    void fillTranslationStream();
};
}
