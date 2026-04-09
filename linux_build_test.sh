#!/bin/bash

# 测试 NBaseUiKit 在 Linux 下的编译情况
echo "Testing NBaseUiKit compilation on Linux..."

# 检查 Qt 是否安装
if ! command -v qmake &> /dev/null; then
    echo "Error: qmake not found. Please install Qt 6.11.0 or later."
    exit 1
fi

# 检查 g++ 是否安装
if ! command -v g++ &> /dev/null; then
    echo "Error: g++ not found. Please install g++."
    exit 1
fi

# 创建构建目录
mkdir -p linux_build
cd linux_build

# 运行 qmake
echo "Running qmake..."
qmake ../NBaseUiKit/NBaseUiKit.pro

if [ $? -ne 0 ]; then
    echo "Error: qmake failed."
    exit 1
fi

# 运行 make
echo "Running make..."
make -j4

if [ $? -ne 0 ]; then
    echo "Error: make failed."
    exit 1
fi

# 编译示例
echo "Compiling example..."
qmake ../Example/Example.pro
make -j4

if [ $? -ne 0 ]; then
    echo "Error: make example failed."
    exit 1
fi

echo "Success: NBaseUiKit compiled successfully on Linux!"
