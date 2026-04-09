#-------------------------------------------------
#
# Project created by QtCreator 2016-08-05T15:35:45
#
#-------------------------------------------------

QT       += widgets

TARGET = NBaseUiKit
TEMPLATE = lib

DEFINES += NBASEUIKIT_LIBRARY

CONFIG += c++17

# 添加编译器标志以避免内部错误
QMAKE_CXXFLAGS_DEBUG -= -std=gnu++1z
QMAKE_CXXFLAGS_DEBUG += -std=c++17
QMAKE_CXXFLAGS_RELEASE -= -std=gnu++1z
QMAKE_CXXFLAGS_RELEASE += -std=c++17

# 引入源码
include($$PWD/NBaseUiKit_src.pri)

# 引入第三方源码
include($$PWD/3rdparty/3rdparty.pri)
INCLUDEPATH += $$PWD/3rdparty/qrencode/qrencode \

# 引入版本信息
win32: RC_FILE += ./NBaseUiKit_resource.rc

# 引入图片资源
RESOURCES += \
    image_resources.qrc

# 定义输出路径
DESTDIR = ../bin

# 输出编译套件信息
message(Qt version: $$[QT_VERSION])
message(Qt is installed in $$[QT_INSTALL_PREFIX])
message(the NBaseUiKit will create in folder: $$target_path)


