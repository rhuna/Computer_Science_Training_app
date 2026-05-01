@echo off
setlocal

echo ========================================
echo CS Bootcamp Desktop v21 Script Runner
echo ========================================

call "%~dp0smoke_test_v21.bat"
if errorlevel 1 exit /b 1

call "%~dp0clean_build_tree.bat"

echo Done.
exit /b 0
