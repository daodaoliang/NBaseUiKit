#-------------------------------------------------
#
# Project created by QtCreator 2016-08-05T15:36:47
#
#-------------------------------------------------

QT       += core gui widgets

CONFIG += c++17

# 添加编译器标志以避免内部错误
QMAKE_CXXFLAGS_DEBUG -= -std=gnu++1z
QMAKE_CXXFLAGS_DEBUG += -std=c++17
QMAKE_CXXFLAGS_RELEASE -= -std=gnu++1z
QMAKE_CXXFLAGS_RELEASE += -std=c++17

TARGET = NBaseUiKit_Example
TEMPLATE = app


SOURCES += main.cpp \
    nbaseuikittest.cpp

HEADERS  += \
    nbaseuikittest.h

# 定义输出路径
DESTDIR = ../bin

# 引入测试类库
LIBS += -L$$OUT_PWD/../bin/ -lNBaseUiKit
include(../NBaseUiKit/NBaseUiKit_inc.pri)

# 输出编译套件信息
message(Qt version: $$[QT_VERSION])
message(Qt is installed in $$[QT_INSTALL_PREFIX])

RESOURCES += \
    example_resources.qrc

FORMS += \
    nbaseuikittest.ui
