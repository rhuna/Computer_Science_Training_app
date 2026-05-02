@echo off
setlocal

echo ========================================
echo CS Bootcamp Desktop v25 Script Runner
echo ========================================

if exist "%~dp0smoke_test_v24.bat" call "%~dp0smoke_test_v24.bat"
if errorlevel 1 exit /b 1

if exist "%~dp0clean_build_tree.bat" call "%~dp0clean_build_tree.bat"

echo Done.
exit /b 0

call "%~dp0smoke_test_v25.bat"
