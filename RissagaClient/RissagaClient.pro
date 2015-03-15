#-------------------------------------------------
#
# Project created by QtCreator 2015-03-02T23:12:57
#
#-------------------------------------------------

QT       += core

QT       -= gui

CONFIG += c++11

TARGET = RissagaClient
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


INCLUDEPATH += D:\Projects\Rissaga
INCLUDEPATH += D:\Projects\Rissaga\GW_SDL2\include

LIBS += -LD:\Projects\Rissaga\GW_SDL2\i686-w64-mingw32\lib -lmingw32 -lSDL2Main -mwindows -lSDL2 -lSDL2_image -lSDL2_ttf

SOURCES += \
    source/resources/fonts.cpp \
    source/resources/textures.cpp \
    source/main.cpp

HEADERS += \
    source/resources/fonts.h \
    source/resources/textures.h \
    source/utils/math.h \
    source/utils/point.h \
    source/utils/rect.h \
    source/utils/size.h \
    ../common/logging.h \
    ../common/state_machine.h \
    ../common/string.h \
    ../utils/color.h \
    ../utils/math.h \
    ../utils/point.h \
    ../utils/rect.h \
    ../utils/Size.h
