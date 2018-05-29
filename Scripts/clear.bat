rmdir /S /Q %~dp0..\NBaseUiKit\release
rmdir /S /Q %~dp0..\NBaseUiKit\debug
rmdir /S /Q %~dp0..\NBaseUiKit\build_
rmdir /S /Q %~dp0..\Example\build_
rmdir /S /Q %~dp0..\Example\release
rmdir /S /Q %~dp0..\Example\debug
rmdir /S /Q %~dp0..\bin
del /Q %~dp0..\Makefile*
del /Q %~dp0..\NBaseUiKit\Makefile*
del /Q %~dp0..\Example\Makefile*
