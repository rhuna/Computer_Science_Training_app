@echo off
setlocal

echo ========================================
echo CS Bootcamp Desktop v31 Smoke Test
echo ========================================

echo [1] Check key source files...
if not exist src\MainWindow.cpp exit /b 1
if not exist src\BootcampContent.cpp exit /b 1
if not exist include\MainWindow.h exit /b 1

echo [2] Check v31 docs...
if not exist docs\V31_SOLOLEARN_STYLE_COURSE_EXPERIENCE.md exit /b 1
if not exist docs\V31_BUILD_NOTES.md exit /b 1

echo [3] Check content pack...
if not exist content_packs\v31_interactive_course_experience_pack.md exit /b 1

echo [4] Check build script...
if not exist rebuild_clean.bat exit /b 1

echo Smoke test passed.
endlocal
