@echo off
setlocal

echo ========================================
echo CS Bootcamp Desktop v28 Script Runner
echo ========================================

if exist "%~dp0smoke_test_v28.bat" call "%~dp0smoke_test_v28.bat"
if errorlevel 1 exit /b 1

if exist "%~dp0package_release.bat" call "%~dp0package_release.bat"

echo Done.
endlocal
