#-------------------------------------------------
#
# Project created by QtCreator 2011-08-30T23:37:32
#
#-------------------------------------------------
# Directories
DESTDIR = ./build
MOC_DIR = ./build
OBJECTS_DIR = ./build

QT       += testlib
QT       -= gui

TARGET = test
CONFIG   += console debug
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += \
    test/test_portfolio.cpp \
    test/RecordedMarket.cpp \
    src/Market.cpp \
    src/Portfolio.cpp \
    src/Tick.cpp

HEADERS += \
    test/RecordedMarket.h \
    src/Portfolio.h \
    src/Market.h \
    src/Stock.h \
    src/Tick.h \
    src/TickStream.h \

DEFINES += SRCDIR=\\\"$$PWD/\\\"
