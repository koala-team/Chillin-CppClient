#-------------------------------------------------
#
# Project created by QtCreator 2017-09-29T14:19:18
#
#-------------------------------------------------

QT += core
QT += network
QT -= gui

TARGET = ChillinClient
VERSION = 1.2.1
DEFINES += APP_VERSION=$$VERSION

TEMPLATE = lib
CONFIG += staticlib

DEFINES += CHILLINCLIENT_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    network.cpp \
    config.cpp \
    gameclient.cpp \
    helpers/logger.cpp \
    helpers/parser.cpp \
    protocol.cpp \
    core.cpp

HEADERS += \
    ChillinClient \
    chillinclient_global.h \
    network.h \
    config.h \
    gameclient.h \
    base_ai.h \
    realtime_ai.h \
    turnbased_ai.h \
    helpers/blockingconcurrentqueue.h \
    helpers/concurrentqueue.h \
    helpers/logger.h \
    helpers/messages.h \
    helpers/parser.h \
    protocol.h \
    core.h \
    abstract_ai.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES += \
    helpers/messages.ks
