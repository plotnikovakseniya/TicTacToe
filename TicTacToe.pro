TEMPLATE = subdirs
SUBDIRS += NetworkLib
SUBDIRS += GameLib
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
