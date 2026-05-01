@echo off
setlocal
set APP_NAME=CSBootcampDesktop
set QT_PREFIX=C:\Qt\6.11.0\mingw_64
set MINGW_BIN=C:\Qt\Tools\mingw1310_64\bin
set PATH=%MINGW_BIN%;%QT_PREFIX%\bin;%PATH%

cmake -S . -B build-debug -G "MinGW Makefiles" -DCMAKE_PREFIX_PATH=%QT_PREFIX% -DCMAKE_BUILD_TYPE=Debug
if errorlevel 1 exit /b 1
cmake --build build-debug
if errorlevel 1 exit /b 1
build-debug\%APP_NAME%.exe
