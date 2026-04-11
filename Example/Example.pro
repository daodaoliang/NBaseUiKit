#-------------------------------------------------
#
# Project created by QtCreator 2016-08-05T15:36:47
#
#-------------------------------------------------

QT       += core gui widgets

CONFIG += c++17

TARGET = NBaseUiKit_Example
TEMPLATE = app

SOURCES += main.cpp \
    nbaseuikittest.cpp \
    nfontawesometest.cpp

HEADERS  += \
    nbaseuikittest.h \
    nfontawesometest.h

DESTDIR = ../bin

# 配置编译中间件输出目录，避免污染源码
MOC_DIR = build_/moc
UI_DIR = build_/ui
RCC_DIR = build_/rcc
OBJECTS_DIR = build_/obj

LIBS += -L$$OUT_PWD/../bin/ -lNBaseUiKit
include(../NBaseUiKit/NBaseUiKit_inc.pri)

message(Qt version: $$[QT_VERSION])
message(Qt is installed in $$[QT_INSTALL_PREFIX])

RESOURCES += \
    example_resources.qrc \
    image_resources.qrc

FORMS += \
    nbaseuikittest.ui \
    nfontawesometest.ui
