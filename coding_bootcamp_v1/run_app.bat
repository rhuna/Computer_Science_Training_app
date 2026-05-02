@echo off
setlocal
set APP_NAME=CSBootcampDesktop
set QT_PREFIX=C:\Qt\6.11.0\mingw_64
set PATH=%QT_PREFIX%\bin;%PATH%

if exist build\%APP_NAME%.exe (
    build\%APP_NAME%.exe
    exit /b 0
)

echo Could not find build\%APP_NAME%.exe. Run rebuild_clean.bat first.
exit /b 1
