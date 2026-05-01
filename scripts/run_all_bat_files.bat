@echo off
setlocal

echo ========================================
echo CS Bootcamp Desktop v24 Script Runner
echo ========================================

call "%~dp0smoke_test_v24.bat"
if errorlevel 1 exit /b 1

if exist "%~dp0clean_build_tree.bat" call "%~dp0clean_build_tree.bat"

echo Done.
exit /b 0
