@echo off
npx tsc || exit /b 1
node dist/main.js | findstr /C:"PASS_SAFE_LOGIN_REVIEW"
