@echo off
setlocal
set VERSION=v28
set RELEASE_DIR=%~dp0..\release\CSBootcampDesktop_%VERSION%

echo Packaging CS Bootcamp Desktop %VERSION%...
if exist "%RELEASE_DIR%" rmdir /s /q "%RELEASE_DIR%"
mkdir "%RELEASE_DIR%"

if exist "%~dp0..\build\CSBootcampDesktop.exe" copy "%~dp0..\build\CSBootcampDesktop.exe" "%RELEASE_DIR%\"
if exist "%~dp0..\README.md" copy "%~dp0..\README.md" "%RELEASE_DIR%\"
if exist "%~dp0..\docs" xcopy "%~dp0..\docs" "%RELEASE_DIR%\docs\" /E /I /Y
if exist "%~dp0..\content_packs" xcopy "%~dp0..\content_packs" "%RELEASE_DIR%\content_packs\" /E /I /Y
if exist "%~dp0..\examples\v28_gated_course_exercises" xcopy "%~dp0..\examples\v28_gated_course_exercises" "%RELEASE_DIR%\examples\v28_gated_course_exercises\" /E /I /Y

echo Release folder prepared: %RELEASE_DIR%
endlocal
