#!/bin/bash

# NBaseUiKit Linux 编译脚本
echo "Building NBaseUiKit on Linux..."

# 获取脚本所在目录
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

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

# 先清理旧的编译文件
echo "Cleaning previous build..."
"$SCRIPT_DIR/Scripts/clear.sh"

# 创建构建目录（可选，因为现在使用 build_ 子目录）
echo "Running qmake..."
cd "$SCRIPT_DIR"
qmake NBaseUiKit.pro

if [ $? -ne 0 ]; then
    echo "Error: qmake failed."
    exit 1
fi

# 运行 make
echo "Running make..."
make -j$(nproc)

if [ $? -ne 0 ]; then
    echo "Error: make failed."
    exit 1
fi

echo "Success: NBaseUiKit compiled successfully on Linux!"
echo "Output files are in: $SCRIPT_DIR/bin/"
