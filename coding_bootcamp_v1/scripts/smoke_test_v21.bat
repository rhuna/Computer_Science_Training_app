@echo off
setlocal

echo ========================================
echo CS Bootcamp Desktop v21 smoke test
echo ========================================

if not exist CMakeLists.txt (
  echo ERROR: Run this script from the repo root.
  exit /b 1
)

if not exist examples\v21_verified_exercises (
  echo ERROR: Missing v21 verified exercise packs.
  exit /b 1
)

if not exist docs\V21_VERIFIED_EXERCISE_PACKS.md (
  echo ERROR: Missing v21 documentation.
  exit /b 1
)

echo OK: v21 file layout is present.
echo Recommended next check: run rebuild_clean.bat, then verify one C++/Python/JavaScript exercise.

endlocal
