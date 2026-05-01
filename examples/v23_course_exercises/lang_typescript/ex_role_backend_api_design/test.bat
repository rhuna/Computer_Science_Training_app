@echo off
npx tsc || exit /b 1
node dist/main.js | findstr /C:"PASS_ROLE_BACKEND_API_DESIGN"
