QT += core network sql
QT -= gui

CONFIG += c++11

TARGET = ZubroQtNetworkServer
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    server.cpp \
    client.cpp

DEFINES += QT_DEPRECATED_WARNINGS

HEADERS += \
    server.h \
    client.h
