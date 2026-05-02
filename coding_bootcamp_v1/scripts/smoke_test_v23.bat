@echo off
setlocal
cd /d "%~dp0.."
echo ========================================
echo CS Bootcamp Desktop v23 Smoke Test
echo ========================================
if not exist CMakeLists.txt echo Missing CMakeLists.txt && exit /b 1
if not exist src\MainWindow.cpp echo Missing MainWindow.cpp && exit /b 1
if not exist docs\V23_REAL_CORRECTNESS_VERIFIER.md echo Missing v23 verifier docs && exit /b 1
if not exist examples\v23_course_exercises echo Missing v23 course exercises && exit /b 1
echo PASS: v23 repo layout exists.
echo Check the app's Verify Correct button to run compile/run/input/output tests.
endlocal
