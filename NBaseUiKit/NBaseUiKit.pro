#-------------------------------------------------
#
# Project created by QtCreator 2016-08-05T15:35:45
#
#-------------------------------------------------

QT       += widgets

TARGET = NBaseUiKit
TEMPLATE = lib

DEFINES += NBASEUIKIT_LIBRARY

CONFIG += c++11

# 引入源码
include($$PWD/NBaseUiKit_src.pri)

# 引入第三方源码
include($$PWD/3rdparty/3rdparty.pri)
INCLUDEPATH += $$PWD/3rdparty/qrencode/qrencode \

# 引入版本信息
RC_FILE += ./NBaseUiKit_resource.rc

# 引入图片资源
RESOURCES += \
    image_resources.qrc

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
        OBJECTS_DIR = $$target_path/obj
}

# 输出编译套件信息
message(Qt version: $$[QT_VERSION])
message(Qt is installed in $$[QT_INSTALL_PREFIX])
message(the NBaseUiKit will create in folder: $$target_path)


