#!/bin/bash

echo "Cleaning NBaseUiKit project..."

# 获取脚本所在目录
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_DIR="$(dirname "$SCRIPT_DIR")"

# 删除 NBaseUiKit 目录下的编译中间件
rm -rf "$PROJECT_DIR/NBaseUiKit/release"
rm -rf "$PROJECT_DIR/NBaseUiKit/debug"
rm -rf "$PROJECT_DIR/NBaseUiKit/build_"
rm -f "$PROJECT_DIR/NBaseUiKit/Makefile"*
rm -f "$PROJECT_DIR/NBaseUiKit/ui_"*.h

# 删除 Example 目录下的编译中间件
rm -rf "$PROJECT_DIR/Example/release"
rm -rf "$PROJECT_DIR/Example/debug"
rm -rf "$PROJECT_DIR/Example/build_"
rm -f "$PROJECT_DIR/Example/Makefile"*
rm -f "$PROJECT_DIR/Example/ui_"*.h

# 删除根目录下的编译中间件
rm -rf "$PROJECT_DIR/bin"
rm -rf "$PROJECT_DIR/build"
rm -f "$PROJECT_DIR/Makefile"*

echo "Clean completed!"
