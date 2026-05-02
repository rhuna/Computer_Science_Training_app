@echo off
setlocal

echo ========================================
echo CS Bootcamp Desktop v28 smoke test
echo ========================================

if not exist CMakeLists.txt (
  echo Run this script from the repo root.
  exit /b 1
)

if not exist src\MainWindow.cpp (
  echo Missing src\MainWindow.cpp
  exit /b 1
)

if not exist examples\v28_gated_course_exercises (
  echo Missing v28 gated exercise folder.
  exit /b 1
)

findstr /C:"One Task at a Time Bootcamp" README.md >nul
if errorlevel 1 (
  echo README does not mention v28 gated workflow.
  exit /b 1
)

echo v28 smoke test passed.
endlocal
