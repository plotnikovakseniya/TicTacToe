TEMPLATE = subdirs
SUBDIRS += GameLib
SUBDIRS += NetworkLib
SUBDIRS += DBServer
SUBDIRS += AuthServer
SUBDIRS += GameServer
SUBDIRS += Client

CONFIG += ordered

DISTFILES += \
    networksettings/networksettings.conf

deployment.path = shared/networksettings
deployment.files = networksettings/networksettings.conf

INSTALLS += deployment
