@echo off
setlocal
set APP_NAME=CSBootcampDesktop
set QT_PREFIX=C:\Qt\6.11.0\mingw_64
set MINGW_BIN=C:\Qt\Tools\mingw1310_64\bin

set PATH=%MINGW_BIN%;%QT_PREFIX%\bin;%PATH%

echo ========================================
echo Rebuilding %APP_NAME% from clean folder
echo ========================================

if exist build rmdir /s /q build

cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_PREFIX_PATH=%QT_PREFIX% -DCMAKE_BUILD_TYPE=Release
if errorlevel 1 goto fail

cmake --build build
if errorlevel 1 goto fail

if exist "%QT_PREFIX%\bin\windeployqt.exe" (
    "%QT_PREFIX%\bin\windeployqt.exe" build\%APP_NAME%.exe
)

if exist build\%APP_NAME%.exe (
    echo.
    echo Build succeeded.
    echo Running app...
    build\%APP_NAME%.exe
    exit /b 0
)

echo Could not find build\%APP_NAME%.exe
goto fail

:fail
echo.
echo Build failed.
exit /b 1
