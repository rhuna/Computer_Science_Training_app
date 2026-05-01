@echo off
npx tsc || exit /b 1
node dist/main.js | findstr /C:"PASS_V15_CROSS_LANGUAGE_API_CLIENT"
