@echo off
echo CS Bootcamp Desktop v35 Smoke Test
if not exist CMakeLists.txt exit /b 1
if not exist src\BootcampContent.cpp exit /b 1
if not exist docs\V35_QUALITY_LESSON_INTERACTIVE_COACHING.md exit /b 1
if not exist content_packs\v35_quality_lessons_pack.md exit /b 1
if not exist examples\v35_quality_lesson_exercises exit /b 1
findstr /C:"lessonFull" src\BootcampContent.cpp >nul || exit /b 1
findstr /C:"INTERACTIVE COACHING WORKFLOW" src\MainWindow.cpp >nul || exit /b 1
echo v35 smoke test passed.
