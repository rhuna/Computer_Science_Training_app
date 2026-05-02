@echo off
setlocal
set VERSION=v35
set RELEASE_DIR=%~dp0..\release\CSBootcampDesktop_%VERSION%
if exist "%RELEASE_DIR%" rmdir /s /q "%RELEASE_DIR%"
mkdir "%RELEASE_DIR%"
if exist "%~dp0..\build\CSBootcampDesktop.exe" copy "%~dp0..\build\CSBootcampDesktop.exe" "%RELEASE_DIR%\"
if exist "%~dp0..\docs" xcopy "%~dp0..\docs" "%RELEASE_DIR%\docs\" /E /I /Y
if exist "%~dp0..\content_packs" xcopy "%~dp0..\content_packs" "%RELEASE_DIR%\content_packs\" /E /I /Y
if exist "%~dp0..\examples\v35_objective_aligned_exercises" xcopy "%~dp0..\examples\v35_objective_aligned_exercises" "%RELEASE_DIR%\examples\v35_objective_aligned_exercises\" /E /I /Y
echo Release package prepared at %RELEASE_DIR%
endlocal

if exist "%~dp0..\examples\v35_split_topic_lessons" xcopy "%~dp0..\examples\v35_split_topic_lessons" "%RELEASE_DIR%\examples\v35_split_topic_lessons\" /E /I /Y
