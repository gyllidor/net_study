TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    SocketFunctions.cpp

HEADERS += \
    SocketFunctions.h \
    BrrLogger.h
