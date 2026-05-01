@echo off
setlocal

set APP_NAME=CSBootcampDesktop
set VERSION=v21
set RELEASE_DIR=%~dp0..\release\%APP_NAME%_%VERSION%

if exist "%RELEASE_DIR%" rmdir /s /q "%RELEASE_DIR%"
mkdir "%RELEASE_DIR%"

if exist "%~dp0..\build\CSBootcampDesktop.exe" copy "%~dp0..\build\CSBootcampDesktop.exe" "%RELEASE_DIR%\"
if exist "%~dp0..\docs" xcopy "%~dp0..\docs" "%RELEASE_DIR%\docs\" /E /I /Y
if exist "%~dp0..\examples" xcopy "%~dp0..\examples" "%RELEASE_DIR%\examples\" /E /I /Y
if exist "%~dp0..\content_packs" xcopy "%~dp0..\content_packs" "%RELEASE_DIR%\content_packs\" /E /I /Y

echo Release folder prepared at:
echo %RELEASE_DIR%
exit /b 0
