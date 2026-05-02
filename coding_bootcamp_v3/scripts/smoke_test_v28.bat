@echo off
setlocal

echo ========================================
echo CS Bootcamp Desktop v31 smoke test
echo ========================================

if not exist CMakeLists.txt (
  echo Run this script from the repo root.
  exit /b 1
)

if not exist src\MainWindow.cpp (
  echo Missing src\MainWindow.cpp
  exit /b 1
)

if not exist examples\v31_complete_curriculum_exercises (
  echo Missing v31 gated exercise folder.
  exit /b 1
)

findstr /C:"Clean Step-by-Step Bootcamp" README.md >nul
if errorlevel 1 (
  echo README does not mention v31 gated workflow.
  exit /b 1
)

echo v31 smoke test passed.
endlocal
