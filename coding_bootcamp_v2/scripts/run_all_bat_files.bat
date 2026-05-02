@echo off
setlocal

echo ========================================
echo CS Bootcamp Desktop v27 Script Runner
echo ========================================

if exist "%~dp0smoke_test_v27.bat" call "%~dp0smoke_test_v27.bat"
if errorlevel 1 exit /b 1

if exist "%~dp0package_release.bat" call "%~dp0package_release.bat"
if errorlevel 1 exit /b 1

echo Done.
exit /b 0
