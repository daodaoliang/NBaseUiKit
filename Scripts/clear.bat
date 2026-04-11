@echo off
echo Cleaning NBaseUiKit project...

REM 删除 NBaseUiKit 目录下的编译中间件
if exist "%~dp0..\NBaseUiKit\release" rmdir /S /Q "%~dp0..\NBaseUiKit\release"
if exist "%~dp0..\NBaseUiKit\debug" rmdir /S /Q "%~dp0..\NBaseUiKit\debug"
if exist "%~dp0..\NBaseUiKit\build_" rmdir /S /Q "%~dp0..\NBaseUiKit\build_"
if exist "%~dp0..\NBaseUiKit\Makefile" del /Q "%~dp0..\NBaseUiKit\Makefile*"
if exist "%~dp0..\NBaseUiKit\ui_*.h" del /Q "%~dp0..\NBaseUiKit\ui_*.h"

REM 删除 Example 目录下的编译中间件
if exist "%~dp0..\Example\release" rmdir /S /Q "%~dp0..\Example\release"
if exist "%~dp0..\Example\debug" rmdir /S /Q "%~dp0..\Example\debug"
if exist "%~dp0..\Example\build_" rmdir /S /Q "%~dp0..\Example\build_"
if exist "%~dp0..\Example\Makefile" del /Q "%~dp0..\Example\Makefile*"
if exist "%~dp0..\Example\ui_*.h" del /Q "%~dp0..\Example\ui_*.h"

REM 删除根目录下的编译中间件
if exist "%~dp0..\bin" rmdir /S /Q "%~dp0..\bin"
if exist "%~dp0..\build" rmdir /S /Q "%~dp0..\build"
if exist "%~dp0..\Makefile" del /Q "%~dp0..\Makefile*"

echo Clean completed!
pause
