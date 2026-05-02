@echo off
setlocal

echo ========================================
echo CS Bootcamp Desktop v23 Guided Course Smoke Test
echo ========================================

if not exist src\MainWindow.cpp (
  echo ERROR: Run this script from the repo root.
  exit /b 1
)

findstr /C:"CS Bootcamp Desktop v23 - Guided Interactive Course" src\MainWindow.cpp >nul
if errorlevel 1 (
  echo ERROR: v23 title missing from MainWindow.cpp
  exit /b 1
)

findstr /C:"AI Tutor Mode" src\MainWindow.cpp >nul
if not errorlevel 1 (
  echo ERROR: AI Tutor Mode should not appear in MainWindow.cpp.
  exit /b 1
)

findstr /C:"Model Adapter Lab" src\MainWindow.cpp >nul
if not errorlevel 1 (
  echo ERROR: Model Adapter Lab should not appear in MainWindow.cpp.
  exit /b 1
)

findstr /C:"Project Generator" src\MainWindow.cpp >nul
if not errorlevel 1 (
  echo ERROR: Project Generator should not appear in MainWindow.cpp.
  exit /b 1
)

if not exist examples\v23_course_exercises (
  echo ERROR: Missing v23 course exercise packs.
  exit /b 1
)

if not exist docs\V23_GUIDED_COURSE_BOOTCAMP.md (
  echo ERROR: Missing v23 documentation.
  exit /b 1
)

echo OK: v23 guided course layout, docs, and exercise packs are present.
exit /b 0
