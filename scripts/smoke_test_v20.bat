@echo off
setlocal

echo ========================================
echo CS Bootcamp Desktop v21 Smoke Test
echo ========================================

if not exist "..\src\MainWindow.cpp" (
  echo FAIL: src\MainWindow.cpp missing
  exit /b 1
)

if not exist "..\examples\v21_verified_exercises" (
  echo FAIL: verified exercise folder missing
  exit /b 1
)

if not exist "..\docs\V21_UNIFIED_LEARNING_SYSTEM.md" (
  echo FAIL: v21 docs missing
  exit /b 1
)

echo PASS: v21 source, docs, and verified exercise folders exist.
exit /b 0
