@echo off
npx tsc || exit /b 1
node dist/main.js
