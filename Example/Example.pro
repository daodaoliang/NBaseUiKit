#-------------------------------------------------
#
# Project created by QtCreator 2016-08-05T15:36:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NBaseUiKit_Example
TEMPLATE = app


SOURCES += main.cpp \
    nbaseuikittest.cpp

HEADERS  += \
    nbaseuikittest.h

# 定义输出路径
win32{
    CONFIG += debug_and_release
    CONFIG(release, debug|release) {
            target_path = ./build_/dist
        } else {
            target_path = ./build_/debug
        }
        DESTDIR = ../bin
        MOC_DIR = $$target_path/moc
        RCC_DIR = $$target_path/rcc
        UI_DIR = $$target_path/ui
        OBJECTS_DIR = $$target_path/obj
}

# 引入测试类库
LIBS += -L$$OUT_PWD/../bin/ -lNBaseUiKit
include(../NBaseUiKit/NBaseUiKit_inc.pri)

# 输出编译套件信息
message(Qt version: $$[QT_VERSION])
message(Qt is installed in $$[QT_INSTALL_PREFIX])
message(the NBaseUiKit_Example will create in folder: $$target_path)

RESOURCES += \
    example_resources.qrc

FORMS += \
    nbaseuikittest.ui
