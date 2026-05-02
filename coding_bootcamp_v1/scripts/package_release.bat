@echo off
setlocal

set APP_NAME=CSBootcampDesktop
set VERSION=v25
set RELEASE_DIR=%~dp0..\release\%APP_NAME%_%VERSION%

if exist "%RELEASE_DIR%" rmdir /s /q "%RELEASE_DIR%"
mkdir "%RELEASE_DIR%"

if exist "%~dp0..\build\CSBootcampDesktop.exe" copy "%~dp0..\build\CSBootcampDesktop.exe" "%RELEASE_DIR%\"
if exist "%~dp0..\docs" xcopy "%~dp0..\docs" "%RELEASE_DIR%\docs\" /E /I /Y
if exist "%~dp0..\examples\v25_guided_problem_solving_exercises" xcopy "%~dp0..\examples\v25_guided_problem_solving_exercises" "%RELEASE_DIR%\examples\v25_guided_problem_solving_exercises\" /E /I /Y
if exist "%~dp0..\content_packs" xcopy "%~dp0..\content_packs" "%RELEASE_DIR%\content_packs\" /E /I /Y
if exist "%~dp0..\advanced_learning_packs" xcopy "%~dp0..\advanced_learning_packs" "%RELEASE_DIR%\advanced_learning_packs\" /E /I /Y

echo Release folder prepared at:
echo %RELEASE_DIR%
exit /b 0
