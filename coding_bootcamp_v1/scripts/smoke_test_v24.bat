@echo off
setlocal
cd /d "%~dp0.."
echo CS Bootcamp Desktop v24 Problem Solving Efficiency Smoke Test
if not exist docs\V24_PROBLEM_SOLVING_EFFICIENCY.md echo Missing v24 docs && exit /b 1
if not exist content_packs\v24_problem_solving_efficiency_pack.md echo Missing v24 content pack && exit /b 1
if not exist examples\v24_problem_solving_exercises echo Missing v24 exercises && exit /b 1
findstr /C:"Problem Solving Coach" src\MainWindow.cpp >nul || (echo Missing Problem Solving Coach page && exit /b 1)
findstr /C:"patternGuideText" include\MainWindow.h >nul || (echo Missing pattern guide declaration && exit /b 1)
echo PASS: v24 problem-solving coach, docs, content pack, and exercise folders are present.
endlocal
